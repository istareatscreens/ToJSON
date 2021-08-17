# ToJSON

A C++11 single-file header-only library to place data into JSON format

To setup just include ToJSON.h header file in your code.

## API

The ToJSON::ToJSON object is used to create JSON objects

The ToJSON::ToArray object is used to create complex arrays to be added to JSON objects

## ToJSON::insert(key, value) : ToJSON

Add key (string), value (any standard C++ types, or ToJSON, ToArray objects) pairs using the insert function. Function can be chained.

```c++
ToJSON::ToJSON obj;

obj.insert("num1", 3.3);

cout<<obj.str(); // prints {"num1": 3.3}

//Can chain insertions
obj.insert("str", "hey")
   .insert("obj",ToJSON::ToJSON{0})
   .insert("arr",ToJSON::ToArray{})
   .insert("void", ToJSON::Null{});

cout<<obj.str(); // prints {"num1": 3.3,"str":"hey","obj":{},"arr":[],"void":null}
```

## ToJSON::insert_array(string key, values... | void) : ToJSON

Add key (string), [values, ...] (any standard C++ types, or ToJSON, ToArray objects) pairs using the insert_array. Function can be chained.

```c++
ToJSON::ToJSON obj;

obj.insert_array("arr1")
    .insert_array("arr2", 3.3, "f")
    .insert_array("arr3", 3.3, "f", -3)

cout<<obj.str(); // prints {"arr1": [],"arr2":[3.3,"f"],"arr3":[3.3,"f",-3]}
```

## ToJSON::empty(void) const : bool

Returns true if JSON object is empty

```c++
ToJSON::ToJSON obj;

cout<<obj.empty() // prints 1 or true
```

## ToJSON::str(void) const : string

Returns the JSON object as a string

```c++
ToJSON::ToJSON obj;

cout<< obj.str() // prints "{}" as object is empty
```

## ToArray::insert(void) : string

Add value (any standard C++ types, or ToJSON, ToArray objects) using the insert function. Function can be chained.

```c++
ToJSON::ToArray arr{}

cout<<arr.str(); // prints "[]"

arr.insert("hey");

cout<<arr.str(); // prints "["hey"]"

arr.insert(3.3)
    .insert(42)
    .insert(ToJSON::Null{});

cout<<arr.str(); // prints "["hey",3.3,42,null]"
```

## ToArray::insert_multiple(values...) : string

Add multiple values (any standard C++ types, or ToJSON, ToArray objects) using the insert function. Function can be chained.

```c++
ToJSON::ToArray arr{}

arr.insert_multiple("hey")
cout<<arr.str(); // prints "["hey"]"

arr.insert_multiple(42,3.3)
cout<<arr.str(); // prints "["hey",43,3.3]"
```

## ToArray::empty(void) const : bool

Returns true if array is empty

```c++
ToJSON::ToArray arr;

cout<<arr.empty() // prints 1 or true
```

## ToArray::str(void) const : string

Returns the array as a string

```c++
ToJSON::ToArray arr;

cout<<arr.str() // prints [] as arr is empty
```

## ToNull

Use "ToJSON::Null{}" to pass: null JSON type as value to ToArray or ToJSON, see insert function examples above
