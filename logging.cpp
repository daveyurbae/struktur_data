// Menerima informasi dari client
int bytes_add = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
if (bytes_add < 0) {
    perror("Gagal menerima data dari client");
    exit(EXIT_FAILURE);
}
buffer[bytes_add] = '\0'; // Null-terminate the received data

printf("Command: %s\n", buffer);

//mengirim keterangan command
send(new_socket, buffer, strlen(buffer), 0);

// Mengirim respons ke client
if (send(new_socket, "Pesan diterima oleh server", strlen("Pesan diterima oleh server"), 0) < 0) {
    perror("Gagal Mengirim Respons ke client");
    exit(EXIT_FAILURE);
}

// memisahkan string dari tanda kutip
char *player = strtok(buffer, "\"");

printf("player: %s\n", player);

// mengambil bagian string yang lain setelah pemisahan
char *cmnd = strtok(NULL, ";");

// melewatkkan karakter spasi yang ada pada command
cmnd += strspn(cmnd, " ");

printf("command: %s\n", cmnd);

//menuliskan di log
log_command(player, cmnd);






//membuat log history command
void log_command(const char *username, const char *command) {
    //menggunakan time saat ini
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    FILE *file = fopen("log.txt", "a");
    if (file == NULL) {
        perror("failed opening log.txt");
        return;
    }

    //menghilangkan ";"
    char cleaned_command[100];
    strcpy(cleaned_command, command);
    char *semicolon_pos = strchr(cleaned_command, ';');
    if (semicolon_pos != NULL) {
        *semicolon_pos = '\0';
    }

    //memasukan file ke log.txt
    fprintf(file, "%s:%s:%s\n", timestamp, username, cleaned_command);

    fclose(file);
}