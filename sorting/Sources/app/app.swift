// This is a basic program on Swift
//
// Try to modify and run it and check out
// the output in the terminal below
//
// Happy coding! :-)

print("Hello, World!");

struct Test: Comparable{
    let index:Int
    let name:String
  static func <(lhs:Test,rhs:Test) -> Bool
  {
    lhs.index < rhs.index
  }
}

var array:[Test] = []
for i in (0...10){
  array.append(Test(index:i,name:"Name\(i)"))
}

print("for..in..sorted")
for val in array.sorted(by:{$0.index > $1.index})
{
  print(val.name)
}

print("print out a copy of a sorted array")
let newarr = array.sorted{$0.index > $1.index}
for temp in newarr
{
  print(temp)
}

print("print out a single element")
if let val = array.first(where:{$0.index==5})
{
 print(val.name)
}





