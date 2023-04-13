# Assignment 1 ADS

#### Task 1: Implementation Instruction:

1. Read the data from the data file specified in the second command line argument.
2. The data from the CSV should be stored in a linked list of pointers to `struct`s for the data.
3. Datatypes for each field should be consistent with those in the ***Dataset\*** slide. Each record (row) should be stored in a separate node.
4. Accept `address`es from *stdin*
5. search the list for all matching records and print them to the output file
6. You may assume that all queries will be terminated by a new line to allow for the querying of footpaths without an address. If no matches for the query are found, your program should output `NOTFOUND`.
7. In addition to outputting the record(s) to the output file, the number of records found should be output to *stdout*.

Note: For testing, it may be convenient to create a file of keys to be searched, one per line, and redirect the input from this file. Use the UNIX operator `<` to redirect input from a file.



## Part 1 - Linked List 

#### 1. 1 struct a linked list**

```c
typedef struct node node_t;

/* value or node inside the linked list*/
struct node {
	record_t data;
	node_t *next; //point to the next node in the list
};

/* structure for a linked list*/
typedef struct {
	node_t *head;
	node_t *foot;
} list_t;
```



#### 1.2 **create a empty linked list**

```c
list_t *make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}
```



#### 1.3 **free a linked list**

```c
void free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}
```

#### **1.4 insert node into a linked list**

```c
list_t *insert_at_head(list_t *list, record_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = list->head;
	list->head = new;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->foot = new;
	}
	return list;
}

list_t *insert_at_foot(list_t *list, record_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}
```



## Part 2 - Read CSV file

#### 2.1 Sample Read CSV file Code in lecture:

```c
int main(int argc, char *argv[]){
    /*make sure to have at least 3 token in the command line*/
	if (argc < 3) {
		fprintf(stderr, "Usage: %s input_file_name output_file_name\n", argv[0]);
		exit(EXIT_FAILURE);
	} 
    
    /*open input and output file, making sure that the names given in the command line is valid*/
    FILE *inFile = fopen(argv[1], "r"),
		 *outFile = fopen(argv[2], "w");
	assert(inFile && outFile);//exit if fails to open files
    
    /* This part is to read the csv file data */
    
    fclose(inFile); //finish read the csv file
    
    fclose(outFile);
    
	return(0);
}
  
```

#### 2.2 Store value

```c
int buildStudentArray(FILE *f, list_t *list) {
	
    // gets rid of the header line
	char line[MAX_LINE_LEN + 1];
	fscanf(f, "%[^\n] ", line);
	// we can also use: while (getchar()!='\n');
    
	// reads and stores students in array students
    int n;
	record_t *r;
	for (n = 0; n < MAX_STUDENTS && (r = readStudent(f)); n++) {
		/* check the node we read and paste it to the linked list */
        
        insert_foot(list, r);//insert every node to the tail of the linked list
       
	}
	return n;
}

record_t *readStudent(FILE *f) {
	record_t *r = NULL;
	int id;
	double score1, score2;
	char name[MAX_NAME_LEN + 1];

    /* replace the item in fscanf */
	if (fscanf(f, "%d, %[^,], %lf , %lf", &id, name, &score1, &score2) == 4) {
        
		/* assign value we read in fscanf to the node r*/
        
        r = malloc(sizeof(*s));     // allocates memory for r
		assert(r);
        
		s->id = id;
		s->name = strdup(name);     // duplicates strings name top s->name
		assert(s->name);           // (function strdup also does malloc) 
        
		s->score1 = score1;
		s->score2 = score2;
	}
	return r;
}
```

