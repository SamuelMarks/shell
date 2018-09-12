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

void close_pipes(int (*)[2], int);

int exec_commands(struct commands *);

void cleanup_commands(struct commands *);
