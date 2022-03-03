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

class Test1{
    init(){
         messageInDelegate = nil
    }
    var messageInDelegate:MessageInDelegate?

    func Hi(){
        guard let msgdelegate = messageInDelegate else{print("Error");return}
        msgdelegate.messageIn(msg:"Hi to you")
    }
}

/*
the Delegate class defines the function, the other class will call into
this class must assign self to the delegate variable in the other class
*/
class Test2:MessageInDelegate{
    var test1:Test1

  init(){
      test1 = Test1()
  }
  func messageIn(msg:String){
      print(msg)
  }
  func sayHiGood(){
    print("Good sayHi")
    test1.messageInDelegate = self
    test1.Hi()
    test1.messageInDelegate = nil
  }
  func sayHiBad(){
    print("Bad sayHi")
    test1.Hi()
  }
}

var test2 = Test2()
test2.sayHiGood()
test2.sayHiBad()