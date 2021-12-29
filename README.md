# SmartIO
SmartIO is a custom language what can be used to transform or define data. Transformations from like table based datasets (SQL, DB) to JSON or XML.
The goal of the project is an easy way to transfrom data from one dataformat to another. 
Usefull for unify API interfaces with support for multiple dataformats, loading external API's into your own Sytem of to export data to a foreign API.
But can also be used as a middleware between two or more systems.

The entire project keeps extendability in mind. Within the language foreign functions can be used. 
The language is functional and descibes how data is structured and/or should be tranformed.
It is possible to link SmartIO language and runtime into another language, or to use it as a standalone tool.

The "drivers" for JSON, XML or datasets are interchangedable and not hot wired.
The project is defined in four parts: Compiler (scanner, parser, compiling), runtime, common library and dataformat drivers.

**At the moment the project is in early alpha phase and lot of the functions are missing. The goal is clear, but there is still lot of open work.
To archive the described goal the following actions are planned (ordered by time):**
 - Setup base structure
 - Frontend + compiler (general purpose part)
 - Backend (incl. runtime) (general purpose part)
 - Logging + error handling
 - Memory management
 - Code cleanup
 - Common lib (min. requirements)
 - Frontend + backend, drivers (early version) for tranforming and defining data
 - API interface
 - ...

## Syntax
**Due to change**

### General purpose
Importing other source code
```
import test.file
```

Configuration
```
config date_format '...'
```

Defining variables (supports for bool, int, float/double and string)
```
int my_var = value
number my_var = value
string my_var = value
date my_date = 02-02-93
...
```

Defining functions
```
func bool Name(bool param1, int param2)
  param1 = 12
  ...
;
```

If statements
```
if (x) || (y)
  ...
;
```

While loop
```
while ()
;
```

Function call
```
my_date.get_day()
```

### Defining and transforming data
Add boolean to the output (single output)
```
add bool ::users[0].name = my_var
```

Add boolean to the output (multi output)
```
add bool mysource::users[0].name = my_var
add bool mysecondsource::users[0].name = xyx
```

Add other formats to the ouput (may with constrains)
```
add bool ...
add str  ...
add int  ...
add date(format=xyz) ::user.birth = :my_date
add str(3, alpha=1)  ::user.name = abc
add str(3)           ::user.name = abc
```

Add array like data to the output
```
add bool ::users[]
add bool ::users[0]

add bool ::parent.item[]
add bool ::parent.item[]

add block ::parent.item
  add str name
  add int age
;

update block ::parent:item // no index = last added item
  add str name
  add int age
;
```

Add attributes to the output (usefull for like XML)
```
add attr ...

add bool users<name=32> = xyx
add bool users<name=32>[] = xyz
add bool users<name=32,age=2> = xyx
```

Namespacing
```
add bool ns:person.ns:name = ...
add bool person.name<ns:name=23> ...
```

Compare output (single output)
```
if ($users[0].name == 123)
```

Compare output (multi output)
```
if ($mysource::users[0].name == 123)
```

Adding data to the output from the input (like a dataset)
```
add bool user = :source_name::abc
```

Calling function from the input
```
:dataset::@my_func
:dataset::FIELD@my_func
```

Escaping and inline variables
```
add bool 'my field'.child.name = ...

add bool users<'my name'=32> = xyx
add bool users<{param1}=32> = xyx
add bool users.{param1}.age = xyz
```

Aliassing
```
var path VAR_NAME my_path
```
