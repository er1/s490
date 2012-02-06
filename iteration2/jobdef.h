
#define JOB_SUCCESS (0)
#define JOB_ERROR (-1)

typedef struct {
	char* ps_name; // FIXME: hardcoded value
	int running; // is this job running?
	pid_t pid; // the pid of the running process
} job_instance;

typedef struct {
	int enabled; // FIXME: hardcoded value
} job_runcondition;

typedef struct { // unused
	int id; // FIXME: hardcoded value
} job_attribute;
