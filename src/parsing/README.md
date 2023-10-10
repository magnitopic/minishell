# Parsing
## Steps

- Initial checks
	- **Check unclosed quotes**
	- **Check invalid redirects**
	- **Check Broken pipes**
- Parse values
	- Separate commands by pipes
	- Split words 
	- Delete empty commands
	- Expand values
		- Separate by group of quotes
		- Parse phrase
			- Remove quotes 
				- Take note in flag
			- Expand variables
		- Join quote groups except for redirects
	* Structure
		* Get command
		* Get arguments
		* Get redirects
