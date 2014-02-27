#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define LINESIZE 80
#define MAX_LINES_PER_PAGE 50

FILE *source_file;
int line_count = MAX_LINES_PER_PAGE;
char header_str[60];

void init_lister(char *str);
bool get_source_line();
void print_line(char *print_buffer);
void print_page_header();

int main(int argc, char **argv)
{
	init_lister(argv[1]);
	if(source_file == NULL)
	{
		perror("Error opening the file.");
		return(-1);
	}
	while(get_source_line());
	fclose(source_file);	
}

void init_lister(char *str)
{
	char *source_name = str;
	source_file = fopen(source_name, "r");
	char date_time[35];
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(date_time, sizeof(date_time)-1, "%a %b %d %T %Y", t);
	sprintf(header_str,"%s %s",source_name,date_time);
}

bool get_source_line()
{
	static int line_number = 0;
	char *source_buffer;
	char print_buffer[90];
	if(fgets(source_buffer,LINESIZE,source_file) != NULL)
	{
		line_number++;
		sprintf(print_buffer,"%d: %s\n",line_number,source_buffer);
		print_line(print_buffer);
	}else
	{
		return false;
	}
	return true;
}

void print_line(char *print_buffer)
{
	if(line_count < MAX_LINES_PER_PAGE)
	{
		line_count++;
		printf(print_buffer);
	}else
	{
		line_count = 0;
		print_page_header();
		print_line(print_buffer);
	}
}

void print_page_header()
{
	static int page_number = 0;
	char print_head_buffer[200];
	page_number++;
	sprintf(print_head_buffer,"Page %d %s",page_number,header_str);
	puts(print_head_buffer);
	puts("");
}
