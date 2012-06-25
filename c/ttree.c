/* file     : ttree.c
 * desc     : Linux显示文件树形结构信息
 * 
 * update   : 
 *              2011.12.23  created
 *              2011.12.25  添加三个参数"-a","-d" and "-L n" .
 * */

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#define MAX_DEPTH       64
#define MAX_FILE_LEN    256

/* 全局变量 */
int _all_file = 0;
int _dir_only = 0;
int _dir_depth = MAX_DEPTH;

void usage()
{
    printf("%s\n",
            "ttree  [-ad] [-L num] path\n\
    -a          All files are listed.\n\
    -d          List directories only.\n\
    -L level    Descend only level directories deep.\n\
            "
            );
}

void print_dirfile(prestr, filename, pdiren)
const char *prestr;
const char *filename;
const char *pdiren;
{
    if (NULL == pdiren) {
        /* 如果当前输出的目录项是最后一项。 */
    	printf("%s%s%s\n", prestr, "`-- ", filename);
    } else {
	    printf("%s%s%s\n", prestr, "|-- ", filename);
    }
}

int __tree_dir(dirname, preindentation, depth)
const char *dirname;
const char *preindentation;
int depth;
{
	DIR *pdir;
	struct stat file_stat;
	struct dirent diren;
	struct dirent nextdiren;
	struct dirent *pdiren;
	char *tmpname;
	char *nowindentation;

	if (depth > MAX_DEPTH)
		return -1;

	if (depth > _dir_depth)
		return -1;

	/*  如果指定了子目录级数，高于该级数的目录就略过 */
	if (depth > _dir_depth)
		return 0;

	tmpname = malloc(MAX_FILE_LEN);
	nowindentation = malloc(MAX_FILE_LEN);
	bzero(nowindentation, MAX_FILE_LEN);

	pdir = opendir(dirname);
	if (NULL == pdir) {
		printf("%s %s\n", dirname, strerror(errno));
		return -1;
	}

	/* diren是当前要处理的目录项 */
	if (readdir_r(pdir, &diren, &pdiren)) {
		printf("%s\n", strerror(errno));
		goto ERR;
	}

	do {
		/* nextdiren是下一次要处理的目录项
		 * pdiren == NULL 时表示 当前的diren是最后一个目录项
		 */
		if (readdir_r(pdir, &nextdiren, &pdiren)) {
			printf("%s\n", strerror(errno));
			goto ERR;
		}
		//if (NULL == pdiren)
		//      break;

		if (strcmp(".", diren.d_name) == 0
		    || strcmp("..", diren.d_name) == 0) {
			goto NEXT_LOOP;
			//continue;
		}

		if (_all_file != 1 && strncmp(".", diren.d_name, 1) == 0) {
			goto NEXT_LOOP;
			//continue;
		}

		snprintf(tmpname, MAX_FILE_LEN, "%s/%s", dirname, diren.d_name);
		bzero(&file_stat, sizeof(file_stat));
		if (-1 == stat(tmpname, &file_stat)) {
			printf("%s\n", strerror(errno));
			goto ERR;
		}
       
        /* 如果仅显示目录，则不显示文件, 跳过此次循环 */
        if (_dir_only == 1 && !S_ISDIR(file_stat.st_mode)) {
            goto NEXT_LOOP;
        }
		
        print_dirfile(preindentation, diren.d_name, pdiren);

		if (S_ISDIR(file_stat.st_mode)) {
			strcpy(nowindentation, preindentation);
            /* 如果当前目录项是最后一项，那么下一层目录的输出就不需要符号“|” */
            if (NULL == pdiren) {
                strcat(nowindentation,"   ");
            } else {
			    strcat(nowindentation, "|   ");
            }
			__tree_dir(tmpname, nowindentation, depth + 1);
		}

	      NEXT_LOOP:
		/* 下一次循环处理下一个目录项 : 值传递 */
		diren = nextdiren;
	} while (pdiren != NULL);

	closedir(pdir);
	free(tmpname);
	free(nowindentation);
	return 0;

      ERR:
	closedir(pdir);
	free(tmpname);
	free(nowindentation);
	return -1;
}

int main(int argc, char **argv)
{
    int c;

	if (argc < 2) {
        usage();
        return -1;
    }
    while(1) {
        c = getopt (argc, argv, "adL:");
        if (c == -1) {
            break;
        }
        switch(c) {
            case 'a':
                //printf ("option a\n");
                _all_file = 1;
                break;
            case 'd':
                //printf ("option d\n");
                _dir_only = 1;
                break;
            case 'L':
               // printf ("option L with additional value `%s'\n", optarg);
                _dir_depth = atoi(optarg);
                break;

            default :
                usage();
                //exit 1;
                break;
        }
    }
    printf("%s\n",argv[argc - 1]);
	return __tree_dir(argv[argc - 1], "", 0);
}
