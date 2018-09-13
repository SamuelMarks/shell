/* Constants */
#define ARG_MAX_COUNT    1024      /* max number of arguments to a command */

/* Type declarations */
struct command {		   /* a struct that stores a parsed command */
	int argc;                  /* number of arguments in the comand */
	char *name;                /* name of the command */
	char *argv[ARG_MAX_COUNT]; /* the arguments themselves */
	int fds[2];                /* the file descriptors for input/output */
};

struct commands {                  /* struct to store a command pipeline */
	int cmd_count;             /* number of commands in the pipeline */
	struct command *cmds[];    /* the commands themselves */
};


int exec_command(struct commands*, struct command*, int (*)[2]);

int is_blank(char *);

/* Parses a single command into a command struct.
 * Allocates memory for keeping the struct and the caller is responsible
 * for freeing up the memory
 */
struct command *parse_command(char *);


/* Parses a command with pipes into a commands* structure.
 * Allocates memory for keeping the struct and the caller is responsible
 * for freeing up the memory
 */
struct commands *parse_commands_with_pipes(char *);


int run_cmd(const char *s);

static inline int run_command(const char *, bool);

/* Returns whether a command is a built-in. As of now
 * one of [exit, cd]
 */
int check_built_in(struct command *);


/* Handles the shell built-in commands. Takes the input/output file descriptors
 * to execute the built-in against. Since none of the built-ins read input from
 * STDIN, only the value of output fd is to be used that too only for the
 * history command since that is the only command that writes to STDOUT.
 *
 * Returns -1 to indicate that program should exit.
 */
int handle_built_in(struct commands *, struct command *);


/* Executes a command by forking of a child and calling exec.
 * Causes the calling progress to halt until the child is done executing.
 */
int exec_command(struct commands *, struct command *, int (*)[2]);

/* closes all the pipes */
void close_pipes(int (*)[2], int);

/* Executes a set of commands that are piped together.
 * If it's a single command, it simply calls `exec_command`.
 */
int exec_commands(struct commands *);


/* Frees up memory for the commands */
void cleanup_commands(struct commands *);

/* Process all input commands */
int processInput(const char *, const bool);
