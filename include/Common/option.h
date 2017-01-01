#ifndef STRUCT_OPTION_H_

struct option		/* specification for a long form option...	*/
{
	const char *name;		/* option name, without leading hyphens */
	int         has_arg;		/* does it take an argument?		*/
	int        *flag;		/* where to save its status, or NULL	*/
	int         val;		/* its associated status value		*/
};

enum    		/* permitted values for its `has_arg' field...	*/
{
	no_argument = 0,      	/* option never takes an argument	*/
	required_argument,		/* option always requires an argument	*/
	optional_argument		/* option may take an argument		*/
};

#endif // !STRUCT_OPTION_H_