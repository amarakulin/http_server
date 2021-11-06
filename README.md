### Description

  A web server working on http protocol(mini version of nginx).
  * Allow methods: GET, POST, PUT, DELETE
  * Support custom config file.

# Run Server
To start the server go throught next steps:
  1. git clone the repository on your machine 
  2. run the command `make` in the root of the project
  3. execute the binar file `./webserver` with argument of your configfile. Example: `./webserver server.conf`

# Server configuration
You can configurate your server in any text file by the next rule

Required parameters:
  * `listen` - [Int:Int] (Int - ip, Int - port)
Optional parameters:
  * `server_name` - [String] (name of the server)
  * `root` - [String] (path to default root location in the server)
  * `error_page` - [int String] (int - error code, String path to custom error pages)
  * `client_max_body_size` - [Int][String] (Int - value, String - mesure of the byte(B, K, M))
  * `location` - [String] (uri)
`location` could have a next fields(each field starts from [... ]):
  * `root` - [String] (root path to search file in the server)
  * `index` - [String String ...] (list of filenames to search in the location)
  * `methods` - [String String ...] (list of enable methods)
  * `cgi_extension` - [String] (work only with `.php` files)
  * `cgi_path` - [String] (path to cgi binaru file)
  * `return 301` - [String] (path or url to redirect)
  * `upload_enable`- [String] (`on` or `off`)
  * `client_max_body_size` - [Int][String] (Int - value, String - mesure of the byte(B, K, M))
  
Example configurations files are `server.conf`, `tester_config.conf`
