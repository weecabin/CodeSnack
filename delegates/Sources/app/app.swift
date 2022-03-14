// This is a basic program on Swift
//
// Try to modify and run it and check out
// the output in the terminal below
//
// Happy coding! :-)

print("Hello, World!");

protocol MessageInDelegate{
    func messageIn(msg:String)
}

/*
This class will call the delegate (callback) function as long
as its delegate variable is not nil
*/

class Test1{
    var messageInDelegate:MessageInDelegate?

  var msgInDel:[MessageInDelegate] = []

  func AddDelegate(del:MessageInDelegate){
      msgInDel.append(del)
  }
    func Hi(){
        if let msgdelegate = messageInDelegate
      {
         msgdelegate.messageIn(msg:"Hi to you")
      }else
    {
       print("No delegate registered")
    }
        
      if msgInDel.count>0{
          for i in (0...msgInDel.count-1){
            msgInDel[i].messageIn(msg:"Hi \(i)")
          }
      }
    }
}

/*
the Delegate class conforms to the protocol and defines the function, the other class will call into
this class. must assign self to the delegate variable in the other class
*/
class Test2:MessageInDelegate{

  func messageIn(msg:String){
      print("in test2 delegate: \(msg)")
  }
}
class Test3:MessageInDelegate{

  func messageIn(msg:String){
      print("in test3 delegate: \(msg)")
  }
}
var test3 = Test3()
var test2 = Test2()
var test1 = Test1()

print("\none to one delegate without registering...")
test1.Hi()
print("Now register...")
test1.messageInDelegate = test2
test1.Hi()

print("\ntry the array delegate...")
test1.messageInDelegate = nil
test1.AddDelegate(del:test2)
test1.AddDelegate(del:test3)
test1.AddDelegate(del:test3)
test1.Hi()
