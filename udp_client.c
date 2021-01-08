#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{

  // UDP Soket oluştur
  int socket_desc;
  socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // AF_INET = IPv4 , SOCK_STREAM = TCP

  if(socket_desc < 0){
    printf("HATA: Soket oluşturulamadı!\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Soket başarıyla oluşturuldu.\n");

  // Server adresini oluştur
  struct sockaddr_in server_addr;
  socklen_t server_socklen = sizeof(server_addr);

  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(3000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Gönderilecek mesajı oluştur
  char client_message[1024];
  printf("İletmek istediğiniz mesajınızı giriniz: ");
  fgets(client_message, 1024, stdin);
  strtok(client_message, "\n");

  // Oluştulan mesajı sunucuya gönder
  int send_result;
  send_result = sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr*) &server_addr, sizeof(server_addr));

  if(send_result < 0){
    printf("HATA: Mesaj gönderme işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Mesaj gönderme işlemi başarılı oldu.\n");

  // Sunucudan gelecek cevap için bellekten alan ayır
  char server_message[1024];
  memset(server_message, '\0', sizeof(server_message));

  // Sunucudan gelecek olan cevabı oku
  int receive_result;
  receive_result = recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr*) &server_addr, &server_socklen);

  if(receive_result < 0){
    printf("HATA: Sunucudan mesaj alma işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Sunucudan mesaj başarıyla alındı. Mesaj: %s\n", server_message);

  close(socket_desc);

  return EXIT_SUCCESS;
}
