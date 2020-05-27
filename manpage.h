
char help_txt[1024] = "TrackBug [Option [value]]\nOptions:\n-u\t--user\tReport bug. Requires login.\n-a\t--admin\t\tlogin as admin. Admin can change status of bug and modify bug reports.\n-h\t--help\t\tView help section of TrackBug.";

void help()
{
	printf("%s\n", help_txt);
}
