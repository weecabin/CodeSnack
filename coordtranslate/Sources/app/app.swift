// This is a basic program on Swift
//
// Try to modify and run it and check out
// the output in the terminal below
//
// Happy coding! :-)

/*
(0,0) is lower left corner
*/
class Screen{
    var minWorldX:Double
    var minWorldY:Double
    var maxWorldX:Double
    var maxWorldY:Double
    var maxScreenX:Int
    var maxScreenY:Int
    
    init(minWorldX:Double=0, minWorldY:Double=0,maxWorldX:Double=100,maxWorldY:Double=1000,maxScreenX:Int=200,maxScreenY:Int=200){
        self.minWorldX = minWorldX
        self.minWorldY = minWorldY
        self.maxWorldX = maxWorldX
        self.maxWorldY = maxWorldY
        self.maxScreenX = maxScreenX
        self.maxScreenY = maxScreenY
    }
    
    var worldToScreenScaleX:Double{
        Double(maxScreenX) / (maxWorldX - minWorldX)
    }
    var worldToScreenScaleY:Double{
        Double(maxScreenY) / (maxWorldY - minWorldY)
    }
    
    func worldY(screenY:Int)->Double{
        let wy = Double(screenY)/worldToScreenScaleY + minWorldY
        return wy
    }
    func worldX(screenX:Int)->Double{
        let wx = Double(screenX)/worldToScreenScaleX + minWorldX
        return wx
    }
    
    func screenX(worldX:Double)->Int?{
        if (worldX < minWorldX) || (worldX > maxWorldX) {return nil}
        let x = worldX - minWorldX
        return Int(x * worldToScreenScaleX)
    }
    func screenY(worldY:Double)->Int?{
        if (worldY < minWorldY) || (worldY > maxWorldY) {return nil}
        let y = worldY - minWorldY
        return Int(y * worldToScreenScaleY)
    }
    func screenXY(worldX:Double, worldY:Double)->(x:Int,y:Int)?{
        if let sx = screenX(worldX:worldX),
           let sy = screenY(worldY:worldY){
            return (x:sx,y:sy)
        }
        return nil
    }
}

var screen = Screen()
screen.minWorldX = 200
screen.maxWorldX = 1000
var x:Double = -100.0

while x < 1200{
  let y = 0.5 * x
  print("(x:\(x),y:\(y)) = ")
  if let scrX = screen.screenX(worldX: x),
     let scrY = screen.screenY(worldY: y){
  print("\(scrX),\(scrY)\n")
  }else{
    print("off screen\n")
  }
  x += 100
}

if let xy = (screen.screenXY(worldX:400,worldY:500)){
  print("x,y = \(xy.x),\(xy.y)")
}else{
  print("x,y... off screen")
}


