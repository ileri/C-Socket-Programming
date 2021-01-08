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
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(3000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Soketi adrese "bind" et ( bağla ).
  int bind_result;
  bind_result = bind(socket_desc, (struct sockaddr*) &server_addr, sizeof(server_addr));

  if(bind_result < 0){
    printf("HATA: Bind işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Port Numarası: %d\n", ntohs(server_addr.sin_port));
  printf("BİLGİ: Bind işlemi başarılı.\n");

  // İstemci adresi oluştur
  struct sockaddr_in client_addr;
  socklen_t client_socklen = sizeof(client_addr);

  // İstemciden alınacak mesaj için hafızada yer ayır
  char client_message[1024];

  int receive_result;
  int send_result;
  char server_message[] = "Merhaba. Mesajınız bize ulaştı.";

  while(1){
    memset(client_message, '\0', sizeof(client_message));

    // İstemciden mesajı al
    receive_result = recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*) &client_addr, &client_socklen);

    if(receive_result < 0){
      printf("HATA: Mesaj alma işlemi başarısız oldu.\n");
    }

    printf("BİLGİ: Mesaj alma işlemi başarılı oldu. Mesaj: %s\n", client_message);
    
    send_result = sendto(socket_desc, server_message, strlen(server_message), 0, (struct sockaddr*) &client_addr, client_socklen);

    if(send_result < 0){
      printf("HATA: Mesaj gönderme işlemi başarısız oldu.\n");
    }

    printf("BİLGİ: Mesaj gönderme işlemi başarılı oldu.\n");
  }

  close(socket_desc);

  return EXIT_SUCCESS;
}
