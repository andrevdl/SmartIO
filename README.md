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
