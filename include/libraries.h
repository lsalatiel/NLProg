#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "classes.h"
#include "document_info.h"
#include "forward_index.h"
#include "functions.h"
#include "indexes.h"
#include "inverted_index.h"
#include "text_info.h"
#include "word_info.h"

#define ONLINE 1
#define RED "\e[31m"
#define BOLD "\e[1m"
#define GREEN "\e[32m"
#define DEFAULT "\e[0m"
#define BUFFER_SIZE 128
#define STARTER_ALLOC 16
#define MAX_RESULTS_NUMBER 10
#define MAX_CLASSES_NUMBER 10
#define CLEAR_TERMINAL system("clear")

#endif