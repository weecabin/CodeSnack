// This is a basic program on Swift
//
// Try to modify and run it and check out
// the output in the terminal below
//
// Happy coding! :-)
// Testing

class TranslateHeading{
    var headingAtApZero:Float
  
    init(headingAtApZero:Float){
       self.headingAtApZero = headingAtApZero
       NewZeroHeading(heading:headingAtApZero) 
    }

  func NewZeroHeading(heading:Float){
      print("Set \(heading) = AP 0")
      headingAtApZero = heading
  }

  func ApHeading(stearHeading:Float) -> Float
  {
     let ret:Float = FixHeading(heading: stearHeading - headingAtApZero)
     return ret
  }

  func FixHeading(heading:Float) -> Float
  {
    var h = heading
    while h<=0 {
      h = h + 360
    }
  
    while h>360 {
      h = h - 360
    }
  return h;
  }
}

let translate = TranslateHeading(headingAtApZero:40)

var h:Float = 55
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")

h = 30
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")

h = 350
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")

translate.NewZeroHeading(heading:330)
h = 30
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")

h = 350
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")

h = 310
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")

h = 90
print("true heading \(h) = AP \(translate.ApHeading(stearHeading:h))")