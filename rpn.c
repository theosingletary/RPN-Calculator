#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct stack {
	int data;
	struct stack *bottom;
} stack;

void push (stack **top, int value){
	stack *node = malloc(sizeof(stack));
	node->data = value;
	node->bottom = *top;
	*top = node;
}

int pop(stack **top) {
	stack *temp = *top;
	int value = temp->data;
	*top = temp->bottom;
	free(temp);
	return value;
}

void pstack(stack *top, int first) {
    if (!top) { 
        if (first) 
            puts ("[ ]"); 
        return; 
    }
    pstack(top->bottom, 0);
    printf("%c %d", (top->bottom ? ',' : '['), top->data);
    if (first) 
        puts(" ]");
}

//returns 0 if invalid, 1 if num, 2 if op
int checker(char *curTok) {
	
	int tokLen = strlen(curTok);

	if(tokLen == 1) {
		if (isdigit(curTok[0]) != 0) {
		   	return 1;
		}
		else if(curTok[0]=='+'|curTok[0]=='-'|curTok[0]=='*'|curTok[0]=='/') {
		   return 2;
		}
	}

	else if (tokLen > 1) {
		if ((isdigit(curTok[0]) != 0) || (curTok[0]=='-')) {
			for (int i = 1; i < tokLen; i++) {
	    		if (isdigit(curTok[i]) == 0) {
	    			return 0;
	    		}
	   		}
	   		return 1;
	   	}
   	}

   	return 0;
}



int main() {

	char *arr = (char *)malloc(4096 * sizeof(char));
	int value;
	int stackLen = 0;
	stack *head = NULL;
	int temp_1;
	int temp_2;
	int buffCount = 0;
	int capacity= 4096;

	while(fgets(arr,capacity,stdin)) {

		buffCount++;
		printf("BuffCount %i\n", buffCount);

		if (buffLen >= capacity) {
			capacity *= 2;
			arr = (char *)realloc(arr, capacity * sizeof(char));
		}

		char *token = strtok (arr, " \n");

		while (token != NULL){

		    char *curTok = token;
		    //int tokLen = strlen(curTok);

		    int checked = checker(curTok);
		    
		    if(checked == 1) {
		    	value = atoi(curTok);
		        push(&head, value);
		        stackLen++;

		        pstack(head, stackLen);

		        token = strtok (NULL, " \n");
		    }

		    else if(checked == 2){
        
            	if(stackLen>=2){
                	temp_1=pop(&head);
              		temp_2=pop(&head);

             		if(curTok[0]=='+'){
           				value=temp_2+temp_1;
            		}
            		else if(curTok[0]=='-'){
            			value=(temp_2-temp_1);
            		}
            		else if(curTok[0]=='*'){
            			value=(temp_2*temp_1);
            		}
            		else if(curTok[0]=='/'){
            			value=(temp_2/temp_1);
            		}

           		push(&head, value);
         
            		stackLen--;

            		pstack(head, stackLen);

            		token = strtok(NULL, " \n");
        		}
        		else {
        			pstack(head, stackLen);
           			return 0;
       			}
    		}

    		else {
    			pstack(head, stackLen);
 				return 0;
    		}
		}
	}

}
