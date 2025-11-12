import numpy as np
import cv2
import matplotlib.pyplot as plt
from scipy.spatial import distance
import os
import shutil


output_dir = './rrt/'
try:
    shutil.rmtree(output_dir)
except FileNotFoundError:
    pass
os.makedirs(output_dir, exist_ok=True)

def addRectangle(image, x0, y0, height, width):
    '''Function to add rectangular obstacles to our world. Note that (0,0) corresponds to the top left corner
    of the image'''
    image[y0:y0+height, x0:x0+width, :] = 0
    return image

def addCircle(image, center_x, center_y, radius, colour=(0,0,0), thickness=-1):
    '''Function to add circular obstacles to our world. Note that (0,0) corresponds to the top left corner
    of the image'''
    return cv2.circle(image, (center_x, center_y), radius, colour, thickness)

def addBorders(world, border_thickness=10):
    world[:, :border_thickness, :] = 0  # Left border
    world[:border_thickness, :, :] = 0  # Top border
    world[:, -border_thickness:, :] = 0  # Right border
    world[-border_thickness:, :, :] = 0  # Bottom border
    return world

def createWorld(height, width, start_point, goal_point):
    '''Function to make the world/occupancy grid with a new environment.'''
    # Create an empty space of size heightxwidth
    world = np.uint8(np.full((height, width, 3), 255))
    
    # Add thicker borders to our empty space
    world = addBorders(world, border_thickness=10)

    # Add new rectangular obstacles to the world
    world = addRectangle(world, x0=50, y0=100, height=100, width=30)  # Vertical rectangle in upper-left
    world = addRectangle(world, x0=220, y0=50, height=30, width=60)   # Horizontal rectangle in upper-right
    world = addRectangle(world, x0=100, y0=220, height=60, width=40)  # Rectangle in lower-middle
    
    # Add new circular obstacles to the world
    world = addCircle(center_x=100, center_y=50, radius=15, image=world)   # Circle in upper-middle
    world = addCircle(center_x=200, center_y=150, radius=30, image=world)  # Circle in middle-right
    
    # Mark start and end points on the world
    world = addCircle(image=world, center_x=start_point[0], center_y=start_point[1],
                      radius=5, colour=(0,0,255), thickness=-1)  # Draw a blue circle representing start
    world = addCircle(image=world, center_x=goal_point[0], center_y=goal_point[1],
                      radius=5, colour=(0,255,0), thickness=-1)  # Draw a green circle representing goal

    '''The empty spaces in the world correspond to the points where world[i][j]=255 and obstacles correspond to 
    places where world[i][j]=0'''
    
    return world

def obstacleCount(world):
    return (world == [0, 0, 0]).all(axis=2).sum()

def getFreeSpaces(world):
    return np.array(np.where((world == [255, 255, 255]).all(axis=2))).T 

def rrt(start_point, goal_point, world, step_length=10, threshold=5):
    obstacle_count = obstacleCount(world)
    free_spaces = getFreeSpaces(world)  # obstacle-free space
    tree = []
    tree.append(list(start_point))
    tree = np.array(tree)

    frame_count = 0
    while True:
        rdm_idx = np.random.randint(len(free_spaces))
        x_k = free_spaces[rdm_idx]
        closest_index = distance.cdist([x_k], tree).argmin()

        x_n = tree[closest_index]
        x_s = x_n + step_length * (x_k - x_n) / np.linalg.norm(x_k - x_n)
        x_s = x_s.astype(int)

        # Check if x_s is in free space by verifying pixel value
        if not (0 <= x_s[0] < world.shape[1] and 0 <= x_s[1] < world.shape[0] and
                np.all(world[x_s[1], x_s[0]] == [255, 255, 255])):
            continue
        
        world_copy = np.copy(world)
        world_copy = cv2.line(world_copy, tuple(x_n)[::-1], tuple(x_s)[::-1], (255, 0, 0), 1)
        obstacle_count_new = obstacleCount(world_copy)

        if obstacle_count_new != obstacle_count:
            continue  # collision occurred; skip this iteration

        world = world_copy
        tree = np.array(np.vstack([tree, x_s]))
        free_spaces = getFreeSpaces(world)
        frame_count += 1

        cv2.imwrite(
            os.path.join(output_dir, f"{frame_count:04d}.png"),
            world,
            [cv2.IMWRITE_PNG_COMPRESSION, 1]  
        )
        if len(free_spaces) <= 0:
            break  # If no more free spaces remaining, break

        goal_distance = distance.cdist([goal_point], tree)
        closest_index = goal_distance.argmin()
        if goal_distance[0, closest_index] <= threshold:
            goal_point = tree[closest_index]
            break  # If within acceptable distance of goal, break

# Define start and end nodes
start_point = (15, 15)
goal_point = (250, 250)

# Initialize and display world
world = createWorld(300, 300, start_point, goal_point)
print("Below is an image of our world.\nBlue dot represents start node,\nGreen dot represents goal node,\n"
      "Black regions represent obstacles\nWhite regions represent empty spaces\n")
plt.figure(figsize=(10, 10))  # Set figure size to 10x10 inches
plt.imshow(world)
plt.axis('off')  # Hide axes for cleaner visualization
plt.savefig('./rrt/initial_world.jpg', dpi=300, bbox_inches='tight')
plt.show()
plt.close()  # Close figure to prevent memory leaks

# Call RRT
rrt(start_point, goal_point, world, threshold=10, step_length=10)