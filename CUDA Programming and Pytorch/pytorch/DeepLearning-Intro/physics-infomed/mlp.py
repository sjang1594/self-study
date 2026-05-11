import torch
import torch.nn as nn
from torch.nn.utils.parametrizations import weight_norm

class LinearBlock(nn.Module):
    def __init__(self, in_nodes, out_nodes):
        super(LinearBlock, self).__init__()
        self.layer = weight_norm(nn.Linear(in_nodes, out_nodes), dim=0)

    def forward(self, x):
        x = self.layer(x)
        x = torch.tanh(x)
        return x

class MLP(nn.Module):
    def __init__(self, layer_list):
        super(MLP, self).__init__()
        self.input_layer = weight_norm(nn.Linear(layer_list[0], layer_list[1]), dim=0)
        self.hidden_layers = self._make_layer(layer_list[1:-1])
        self.output_layer = nn.Linear(layer_list[-2], layer_list[-1])

    def _make_layer(self, layer_list):
        layers = []
        for i in range(len(layer_list) - 1):
            block = LinearBlock(layer_list[i], layer_list[i + 1])
            layers.append(block)
        return nn.Sequential(*layers)

    def forward(self, x):
        x = torch.tanh(self.input_layer(x))
        x = self.hidden_layers(x)
        x = self.output_layer(x)
        return x

class FTransform1D(nn.Module):
    def __init__(self, m, w):
        super(FTransform1D, self).__init__()
        self.m = m
        self.w = w

    def forward(self, x):
        fourier_embd = torch.ones(x.size(0), 1, device=x.device)
        for i in range(1, self.m + 1):
            cos_term = torch.cos(i * self.w * x)
            sin_term = torch.sin(i * self.w * x)
            fourier_embd = torch.cat((fourier_embd, cos_term.unsqueeze(1), sin_term.unsqueeze(1)), dim=1)
        return fourier_embd

class FMLP(nn.Module):
    def __init__(self, layer_list):
        super(FMLP, self).__init__()
        # L=2
        # w=2pi/L= torch.pi
        self.ft = FTransform1D(layer_list[0], torch.pi)
        self.input_layer = weight_norm(nn.Linear(2*layer_list[0]+2, layer_list[1]), dim=0)
        self.hidden_layers = self._make_layer(layer_list[1:-1])
        self.output_layer = nn.Linear(layer_list[-2], layer_list[-1])

    def _make_layer(self, layer_list):
        layers = []
        for i in range(len(layer_list) - 1):
            block = LinearBlock(layer_list[i], layer_list[i + 1])
            layers.append(block)
        return nn.Sequential(*layers)

    def forward(self, x):
        fx = self.ft(x[:,1])
        x = torch.hstack((x[:,0:1],fx))
        x = torch.tanh(self.input_layer(x))
        x = self.hidden_layers(x)
        x = self.output_layer(x)
        return x

def weights_init(m):
    if isinstance(m, nn.Linear):
        nn.init.xavier_normal_(m.weight)

def pinn(layer_list, nfourier=0):
    
    if nfourier > 0:
        print(f"Fourier embedding for boundary conditions in 1D.")
        layer_list[0] = nfourier
        model = FMLP(layer_list)
    else:
        model = MLP(layer_list)
    model.apply(weights_init)
    return model