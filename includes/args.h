#ifndef READ_ARGS_H
#define READ_ARGS_H

/**
** Number of handled parameters
*/

#define OPTIONS_MAP_LENGTH 2

enum {
	MODE,
  THREADS,
};


/*
** Map used to handle each option :
** name : Char* value
** offset: offset in the structure s_options
*/

typedef struct 	s_options_map {
	char		*name;
	int			offset;
}				t_options_map;

/*
** Structure filled with options passed to program
** !! WARNING !!
** Options in struct s_options must be in the same order
** that the enum
*/

typedef struct s_options {
	int mode;
	int threads;
} t_options;

#endif
