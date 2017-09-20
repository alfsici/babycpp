# babycpp
Custom implemented language which is basically a small, **SMALL** subset of c++, just another learning project.

## Grammar
The main struggle was to be able to generate a formal definition of the rules driving the parsing process, here
below the rules:

## Production rules
First of all some nomenclature:
* Statement: by statement I mean a complete "sentence" a piece of code that makes sense and is valid from start to end
             in a single blob.
* Symbols:
  * () = just simple grouping
  * {} = repetition, at least one
  * [] = optionality
  * |  = or
  * "" = literarl ascii values

**statement** =  (extern|definition|expression) ";"

**extern** = "extern" function_protype

**definition** = datatype identifier ["=" expression] |
                 datatype function_definition

**function_definition** = function_prototype "{"{expressions;} "}"

**function_prototype** = datatype identifier "("[ {datatype identifier "," }] ")" 

**expression** =  primary [{operator expression}] | function_call

**primary** = number|identifier| parentheses_expression

**parentheses_expression** = "(" expression ")"

**function_call** = identifier "(" [{identifier} ","}] ")"


# Static typing

The way I decided to handle static typing is a bottom-up approach. Each statement is evaluated independently and whatever reference might be needed in the current statement must be defined in any previous statement. 

Starting from the bottom, types will be compared between operation taking a left and right-hand side, an implicit conversion will be added when necessary and the type of the operator AST node will be tagged with the resulting type of the operation. Right now, the language supports only integers and floats which simplify life a lot.
Here is a simple example. We have a simple statement of type y* (x + 2), the AST looks something like the following:
##

![alt text](https://github.com/giordi91/babycpp/blob/master/images/graph1.png "Basic AST: step 1")

##
The nodes are color-coded based on the type, each node has a type field, most of the AST after parsing is "data-less", meaning that we don't know what type the variables are, the only known nodes are the VariableAST nodes that come from a declaration, for example:
```c++
int x = 20;
```
The following will boil down to a VariableAST node, with a value pointing to the right-hand side, which is a NumberAST node or can be an expression, the datatype is known at parse time and gets set accordingly. Type is also known for NumberAST nodes and function arguments. 

The code generation starts from the top and works its way down recursively, arriving at the leaves starts generating code and working its way up. In this case, the algorithm will go all the way down to the + binary node. 
It will call the code generation for both left and right-hand side. The right-hand side is simple, the type is known. 
The left-hand side has no known type and needs to look it up. If the variable is defined in the context, either from the previous definition or function argument, it will extract the type and set the AST node type to the corresponding one.

In this case, the variable x is of type float, both branches of the binary operator emitted code now is just a matter of performing the addition, before doing so, the code generation function of the binary operator will check that both types are 
equals, if not, it will perform the necessary casting, where the simple rule is, int gets cast to float.

##

![alt text](https://github.com/giordi91/babycpp/blob/master/images/graph2.png "Basic AST: step 2")

##

Now that both branches have the same type we know the resulting type of the operation, we emit the code and tag the binary operator node with the same type.

##

![alt text](https://github.com/giordi91/babycpp/blob/master/images/graph3.png "Basic AST: step 3")

##

At this point we start to see that the resulting datatypes start to "bubble up" the AST,  we move up one step, we have a product operation, we have a left-hand side of type int, and right hand side of type float, the binary operator will emit code for both branches and cast the int to a float:

##

![alt text](https://github.com/giordi91/babycpp/blob/master/images/graph4.png "Basic AST: step 4")

##

Finally we compute the result and set the resulting datatype:

##

![alt text](https://github.com/giordi91/babycpp/blob/master/images/graph5.png "Basic AST: step 5")

##

Here we evaluated correctly the stament. Finally in the case of a fuction, when we hit a return statement, the resulting type will have "bubbled up" until the return type, and we can easily perform a check against the known required return type and act accordingly.

