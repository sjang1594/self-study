
import simd
import CoreGraphics


let pi = Float.pi

func radians(fromDeg deg: Float) -> Float {
    return (deg / 180) * pi
}

func degrees(fromRad rad: Float) -> Float {
    return (rad / pi) * 180
}

extension Float {
    var radiansToDegree: Float {
        return (self / Float.pi) * 180
    }
    
    var degreesToRadians: Float {
        return (self / 180) * Float.pi
    }
}

extension simd_float4x4 {
    init (translation: SIMD3<Float>) {
        let matrix = float4x4(
            [1,                         0,             0, 0],
            [0,                         1,             0, 0],
            [0,                         0,             1, 0],
            [translation.x, translation.y, translation.z, 1]
        )
        self = matrix
    }
    
    init (scaling: SIMD3<Float>) {
        let matrix = float4x4(
            [scaling.x, 0, 0, 0],
            [0, scaling.y, 0, 0],
            [0, 0, scaling.z, 0],
            [0, 0, 0, 1]
        )
        self = matrix
    }
    
    // perspective devide
    init(scaling: Float) {
        self = matrix_identity_float4x4
        columns.3.w = 1 / scaling
    }
    
    init(rotationX angle: Float){
        let matrix = float4x4(
            [1, 0, 0, 0],
            [0, cos(angle), sin(angle), 0],
            [0, -sin(angle), cos(angle), 0],
            [0, 0, 0, 1]
        )
        self = matrix
    }
    
    init(rotationY angle: Float) {
        let matrix = float4x4(
            [cos(angle), 0, -sin(angle), 0],
            [0, 1, 0, 0],
            [sin(angle), 0, cos(angle), 0],
            [0, 0, 0, 1]
        )
        self = matrix
    }
    
    init(rotationZ angle: Float) {
        let matrix = float4x4(
            [cos(angle), sin(angle), 0, 0],
            [-sin(angle), cos(angle), 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1]
        )
        self = matrix
    }
    
    init(rotation angle: SIMD3<Float>) {
        let rotationX = float4x4(rotationX: angle.x)
        let rotationY = float4x4(rotationY: angle.y)
        let rotationZ = float4x4(rotationZ: angle.z)
        self = rotationX * rotationY * rotationZ
    }
    
    init(rotationYXZ angle: SIMD3<Float>) {
        let rotationX = float4x4(rotationX: angle.x)
        let rotationY = float4x4(rotationY: angle.y)
        let rotationZ = float4x4(rotationZ: angle.z)
        self = rotationY * rotationX * rotationZ
    }
    
    static var identity: float4x4 {
        matrix_identity_float4x4
    }
    
    init(projectionFov fov: Float, near: Float, far: Float, aspect: Float){
        let y = 1 / tan(fov * 0.5)
        let x = y / aspect
        let z = far / (far - near)
        let w = -near * z
        let matrix = float4x4(
            SIMD4<Float>(x, 0, 0, 0),
            SIMD4<Float>(0, y, 0, 0),
            SIMD4<Float>(0, 0, z, 1),
            SIMD4<Float>(0, 0, w, 0)
        )
        self = matrix
    }
}
