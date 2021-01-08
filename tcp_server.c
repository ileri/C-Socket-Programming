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

  // Soketi adrese "bind" et ( bağla ).
  int bind_result;
  bind_result = bind(socket_desc, (struct sockaddr*) &server_addr, sizeof(server_addr));

  if(bind_result < 0){
    printf("HATA: Bind işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Port Numarası: %d\n", ntohs(server_addr.sin_port));
  printf("BİLGİ: Bind işlemi başarılı.\n");

  // Gelecek olan isteği dinle
  int listen_status;
  listen_status = listen(socket_desc, 1);

  if(listen_status < 0){
    printf("HATA: Dinleme işlemi başarısız.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Dinleme işlemi başladı.\n");

  // İstemci adresini ilkle
  struct sockaddr_in client_addr;
  socklen_t client_socklen = sizeof(client_addr);

  // İsteği kabul et
  int client_sock_desc;
  client_sock_desc = accept(socket_desc, (struct sockaddr*) &client_addr, &client_socklen);

  if(client_sock_desc < 0){
    printf("HATA: İstek kabul etme başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: İstek başarıyla kabul edildi.\n");

  // Gelen mesaj için bellekten yer ayır
  char client_message[1024];
  memset(client_message, '\0', sizeof(client_message));

  // İstemciden gelen mesajı al
  int receive_result;
  receive_result = recv(client_sock_desc, client_message, sizeof(client_message), 0);

  if(receive_result < 0){
    printf("HATA: Mesaj alma işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Mesaj alma işlemi başarılı. Mesaj: %s\n", client_message);

  // Cevabı hazırla
  char server_message[] = "Merhaba. İsteğiniz sunucu tarafından alındı.\n";

  // Hazırladığımız mesajı gönder
  int send_result;
  send_result = send(client_sock_desc, server_message, strlen(server_message), 0);

  if(send_result < 0){
    printf("HATA: Mesaj gönderme işlemi başarısız oldu.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Mesaj gönderme işlemi başarılı oldu.\n");

  close(client_sock_desc);
  close(socket_desc);

  return EXIT_SUCCESS;
}
