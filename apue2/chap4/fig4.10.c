#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
//#include <unistd.h>

int
main(int argc, char *argv[])
{
	int			i;
	struct stat	buf;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (stat(argv[i], &buf) < 0) {
			//err_ret("stat error");
            fprintf(stderr, "stat error");
			continue;
		}
        printf("st_dev(%d), st_rdev(%d)\n", buf.st_dev, buf.st_rdev);
		printf("dev = %d/%d", major(buf.st_dev),  minor(buf.st_dev));

		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
			printf(" (%s) rdev = %d/%d",
					(S_ISCHR(buf.st_mode)) ? "character" : "block",
					major(buf.st_rdev), minor(buf.st_rdev));
		}
		printf("\n");
	}

	exit(0);
}
