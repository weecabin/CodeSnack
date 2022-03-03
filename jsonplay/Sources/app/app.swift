// This is a basic program on Swift
//
// Try to modify and run it and check out
// the output in the terminal below
//
// Happy coding! :-)

struct CLLocation{
  let latitude:Double
  let longitude:Double
  let speed:Double
  let course:Double
  let time:String
}

struct MapPin{
  let id:String
  let name:String
  let location:CLLocation
  let notes:String
  init(storedPin:StoredMapPin){
    id = storedPin.id
    name = storedPin.name
    notes = storedPin.notes
    let latitude = storedPin.latitude
    let longitude = storedPin.longitude
    let speed = storedPin.speed
    let course = storedPin.course
    let time = storedPin.time
    location = CLLocation(latitude:latitude,longitude:longitude,speed:speed,course:course,time:time)
  }
}

struct StoredMapPin{
  let id:String
  let name:String
  let notes:String
  let latitude:Double
  let longitude:Double
  let speed:Double
  let course:Double
  let time:String
  init(id:String,name:String,notes:String,latitude:Double,longitude:Double,speed:Double,course:Double,time:String)
  {
    self.id=id
    self.name=name
    self.notes = notes
    self.latitude = latitude
    self.longitude = longitude
    self.speed = speed
    self.course = course
    self.time = time
  }
  init(mapPin:MapPin){
    id = mapPin.id
    name = mapPin.name
    notes = mapPin.notes
    latitude = mapPin.location.latitude
    longitude = mapPin.location.longitude
    speed = mapPin.location.speed
    course = mapPin.location.course
    time = mapPin.location.time
  }
}

let storedMapPin = StoredMapPin(id:"1",name:"Name1",notes:"some notes",latitude:30,longitude:-120,speed:1.2,course:90,time:"5:30")
print(storedMapPin)
let mapPin = MapPin(storedPin:storedMapPin)
print(mapPin)
let storedMapPin2 = StoredMapPin(mapPin:mapPin)
print(storedMapPin2)
