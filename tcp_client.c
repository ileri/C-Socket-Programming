#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{

  // TCP Soket oluştur
  int socket_desc;
  socket_desc = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4 , SOCK_STREAM = TCP

  if(socket_desc < 0){
    printf("HATA: Soket oluşturulamadı!\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Soket başarıyla oluşturuldu.\n");

  // Server adresini oluştur
  struct sockaddr_in server_addr;
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(3000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Hedef adres: 127.0.0.1:3000

  // Bağlantıyı oluştur
  int connect_result;
  connect_result = connect(socket_desc, (struct sockaddr*) &server_addr, sizeof(server_addr));

  if(connect_result < 0){
    printf("HATA: Bağlantı kurulamadı.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Bağlantı başarıyla oluşturuldu.\n");

  // Gönderilecek mesajı oluştur
  char client_message[1024];
  printf("İletmek istediğiniz mesajınızı giriniz: ");
  fgets(client_message, 1024, stdin);
  strtok(client_message, "\n");

  // Mesajı sunucuya gönder
  int send_result;
  send_result = send(socket_desc, client_message, strlen(client_message), 0);

  if(send_result < 0){
    printf("HATA: Mesaj gönderme işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Mesaj gönderme işlemi başarılı oldu.\n");

  // Sunucudan gelecek olan mesaj için hafızada yer ayır
  char server_message[1024];
  memset(server_message, '\0', strlen(server_message));

  // Sunucudan mesajı al
  int receive_result;
  receive_result = recv(socket_desc, server_message, sizeof(server_message), 0);

  if(receive_result < 0){
    printf("HATA: Mesaj alma işlemi başarız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Mesaj alma işlemi başarılı. Mesaj: %s", server_message);

  return EXIT_SUCCESS;
}
