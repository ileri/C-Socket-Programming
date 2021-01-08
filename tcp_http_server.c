#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{

  // HTML dosya içeriğini oku
  FILE *html_data;
  html_data = fopen("index.html", "r");

  char response_data[1024];
  fgets(response_data, 1024, html_data);

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  strcat(http_header, response_data);

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
  listen_status = listen(socket_desc, 5);

  if(listen_status < 0){
    printf("HATA: Dinleme işlemi başarısız.\n");
    return EXIT_FAILURE;
  }

  printf("BİLGİ: Dinleme işlemi başladı.\n");

  // İstemci adresini ilkle
  struct sockaddr_in client_addr;
  socklen_t client_socklen = sizeof(client_addr);
  int client_sock_desc;
  int send_result;

  while(1){
    // İsteği kabul et
    client_sock_desc = accept(socket_desc, (struct sockaddr*) &client_addr, &client_socklen);

    if(client_sock_desc < 0){
      printf("HATA: İstek kabul etme başarısız oldu.\n");
    }

    printf("BİLGİ: İstek başarıyla kabul edildi.\n");

    // Hazırladığımız mesajı gönder
    send_result = send(client_sock_desc, http_header, strlen(http_header), 0);

    if(send_result < 0){
      printf("HATA: Mesaj gönderme işlemi başarısız oldu.\n");
    }

    printf("BİLGİ: Mesaj gönderme işlemi başarılı oldu.\n");

    close(client_sock_desc);
  }

  close(socket_desc);

  return EXIT_SUCCESS;
}
