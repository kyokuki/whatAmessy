// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

int automatedTest(int argc, char* argv[])
{
  CU_BOOL Run = CU_FALSE ;

  setvbuf(stdout, NULL, _IONBF, 0);

  if (argc > 1) {
    if (!strcmp("-i", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_IGNORE);
    }
    else if (!strcmp("-f", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_FAIL);
    }
    else if (!strcmp("-A", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_ABORT);
    }
//    else if (!strcmp("-e", argv[1])) {
//      print_example_results();
//    }
    else {
      printf("\nUsage:  AutomatedTest [option]\n\n"
               "        Options: -i  Run, ignoring framework errors [default].\n"
               "                 -f  Run, failing on framework error.\n"
               "                 -A  Run, aborting on framework error.\n"
//               "                 -e  Print expected test results and exit.\n"
               "                 -h  Print this message.\n\n");
    }
  }
  else {
    Run = CU_TRUE;
    CU_set_error_action(CUEA_IGNORE);
  }

  if (CU_TRUE == Run) {
    if (CU_initialize_registry()) {
      printf("\nInitialization of Test Registry failed.");
    }
    else {
      AddTests();
      CU_set_output_filename("TestAutomated");
      CU_list_tests_to_file();
      CU_automated_run_tests();
      CU_cleanup_registry();
    }
  }

  return 0;
}

int basicTest(int argc, char* argv[])
{
  CU_BasicRunMode mode = CU_BRM_VERBOSE;
  CU_ErrorAction error_action = CUEA_IGNORE;
  int i;

  setvbuf(stdout, NULL, _IONBF, 0);

  for (i=1 ; i<argc ; i++) {
    if (!strcmp("-i", argv[i])) {
      error_action = CUEA_IGNORE;
    }
    else if (!strcmp("-f", argv[i])) {
      error_action = CUEA_FAIL;
    }
    else if (!strcmp("-A", argv[i])) {
      error_action = CUEA_ABORT;
    }
    else if (!strcmp("-s", argv[i])) {
      mode = CU_BRM_SILENT;
    }
    else if (!strcmp("-n", argv[i])) {
      mode = CU_BRM_NORMAL;
    }
    else if (!strcmp("-v", argv[i])) {
      mode = CU_BRM_VERBOSE;
    }
//    else if (!strcmp("-e", argv[i])) {
//      print_example_results();
//      return 0;
//    }
    else {
      printf("\nUsage:  BasicTest [options]\n\n"
               "Options:   -i   ignore framework errors [default].\n"
               "           -f   fail on framework error.\n"
               "           -A   abort on framework error.\n\n"
               "           -s   silent mode - no output to screen.\n"
               "           -n   normal mode - standard output to screen.\n"
               "           -v   verbose mode - max output to screen [default].\n\n"
//               "           -e   print expected test results and exit.\n"
               "           -h   print this message and exit.\n\n");
      return 0;
    }
  }

  if (CU_initialize_registry()) {
    printf("\nInitialization of Test Registry failed.");
  }
  else {
    AddTests();
    CU_basic_set_mode(mode);
    CU_set_error_action(error_action);
    printf("\nTests completed with return value %d.\n", CU_basic_run_tests());
    CU_cleanup_registry();
  }

  return 0;
}

int consoleTest(int argc, char* argv[])
{
    CU_BOOL Run = CU_FALSE ;

  setvbuf(stdout, NULL, _IONBF, 0);

  if (argc > 1) {
    if (!strcmp("-i", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_IGNORE);
    }
    else if (!strcmp("-f", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_FAIL);
    }
    else if (!strcmp("-A", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_ABORT);
    }
//    else if (!strcmp("-e", argv[1])) {
//      print_example_results();
//    }
    else {
      printf("\nUsage:  ConsoleTest [option]\n\n"
               "Options:   -i   Run, ignoring framework errors [default].\n"
               "           -f   Run, failing on framework error.\n"
               "           -A   run, aborting on framework error.\n"
//               "           -e   Print expected test results and exit.\n"
               "           -h   Print this message.\n\n");
    }
  }
  else {
    Run = CU_TRUE;
    CU_set_error_action(CUEA_IGNORE);
  }

  if (CU_TRUE == Run) {
    if (CU_initialize_registry()) {
      printf("\nInitialization of Test Registry failed.");
    }
    else {
      AddTests();
      CU_console_run_tests();
      CU_cleanup_registry();
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int ret;
  //ret = basicTest(argc, argv);
  //ret = automatedTest(argc, argv);
  ret = consoleTest(argc, argv);

  return ret;
}
