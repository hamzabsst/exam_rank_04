#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *get_next_line(int fd)
{
	static char buffer[1024];
	static int pos = 0;
	static int len = 0;
	char *line = malloc(1024);
	int i = 0;
	if (!line)
		return NULL;
	while (1)
	{
		if (pos >= len)
		{
			len = read(fd, buffer, sizeof(buffer));
			if (len <= 0)
			{
				if (i == 0)
				{free(line); return NULL; }
				break;
			}
			pos = 0;
		}
		if (buffer[pos] == '\n')
		{
			pos++;
			break;
		}

		line[i++] = buffer[pos++];
		if (i >= 1023)
			break;
	}
	line[i] = '\0';
	return line;
}
void ft_putstr(const char *s)
{
	if (s) write(1, s, strlen(s));
}
int main()
{
	printf("=== Testing ft_popen with 'r' (reading from ls) ===\n");
	char *argv_ls[] = {"ls", "-l", NULL};
	int fd_r = ft_popen("ls", argv_ls, 'r');
	if (fd_r == -1)
	{
		printf("Error: ft_popen failed\n");
		return 1;
	}
	printf("Reading output from 'ls -l':\n");
	char *line;
	int line_count = 0;
	while ((line = get_next_line(fd_r)) && line_count < 10) // Limit output
	{
		printf("%s\n", line);
		free(line);
		line_count++;
	}
	close(fd_r);
	printf("\n=== Testing ft_popen with 'w' (writing to cat) ===\n");
	char *argv_cat[] = {"cat", NULL};
	int fd_w = ft_popen("cat", argv_cat, 'w');
	if (fd_w == -1)
	{
		printf("Error: ft_popen failed\n");
		return 1;
	}
	printf("Writing to cat (should echo back):\n");
	const char *test_msg = "Hello from ft_popen!\nThis is a test message.\n";
	write(fd_w, test_msg, strlen(test_msg));
	close(fd_w);
	sleep(1);
	printf("\n=== Testing error cases ===\n");
	if (ft_popen(NULL, argv_ls, 'r') == -1)
		printf("✓ NULL file parameter handled correctly\n");
	if (ft_popen("ls", NULL, 'r') == -1)
		printf("✓ NULL argv parameter handled correctly\n");
	if (ft_popen("ls", argv_ls, 'x') == -1)
		printf("✓ Invalid type parameter handled correctly\n");
	char *argv_fake[] = {"nonexistent_command_12345", NULL};
	int fd_fake = ft_popen("nonexistent_command_12345", argv_fake, 'r');
	if (fd_fake != -1)
	{
		close(fd_fake);
		printf("✓ Non-existent command returns fd (child will exit with error)\n");
	}
	printf("\n=== All tests completed ===\n");
	return 0;
}
