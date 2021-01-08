# OMÜ Bilgisayar Mühendisliği - Sistem Programlama Dersi - Soket Programlama

Soket oluşturmak için gerekli fonksiyon ve kütüphane açıklamaları aşağıdadır.

Kaynak kodlar `gcc dosya_adi.c -o derlenmis_dosya` komutu ile derlenebilir,
ekstra bir parametreye gerek yoktur.

## sys/socket.h

Soket oluşturmak için gerekli fonksiyonları içeren başlık dosyasıdır.

## arpa/inet.h

Soket adresi oluşturmak için gerekli olan fonksiyon ve sabitleri içeren
başlık dosyasıdır.
Bu kütüphane içerisinde diğer gerekli alt kütüphaneleri de koda dahil
ettiği için diğer bir çok başlık dosyasını import etmeye gerek kalmaz.

## socket()

Bağlantı için gerekli endpoint (uç birim) oluşturur.
Başarılı olması durumunda bir dosya tanımlayıcısı (file descriptor) döner.
Başarısız olursa da -1 değerini döner.

Parametreleri:

```yaml
1 : Domain ( Specifies the communications domain in which a socket is to be
    created. )
2 : Type ( Specifies the type of socket to be created. )
3 : Protocol ( Specifies a particular protocol to be used with the socket.
    Specifying a protocol of 0 causes socket() to use an unspecified default
    protocol appropriate for the requested socket type.)
```

```yaml
AF_INET  : IPv4 Protokolü
AF_INET6 : IPv6 Protokolü
```

```yaml
SOCK_STREAM : TCP
SOCK_DGRAM  : UDP  
```

```yaml
0           : Varsayılan protokol
IPPROTO_UDP : UDP protokolü
```

## sockaddr_in

 - sin_family : AF_INET olarak belirlenmelidir.

 - sin_port   : Portu belirler.
   - htons      : Port numarasını network byte order'a dönüştürür.

 - sin_addr   : IP host address
   - s_addr     : Host interface address

## bind()

Parametreleri:

```yaml
 1 : Socket file descriptor  ( int )
 2 : Socket address          ( *sockaddr )
 3 : Server address length   ( socketlen_t )
```

## connect()

Parametreleri:

```yaml
 1 : Socket file descriptor  ( int )
 2 : Socket address          ( *sockaddr )
 3 : Server address length   ( socketlen_t )
```

## listen()

Parametreleri:

```yaml
 1 : Socket file descriptor  ( int )
 2 : Backlog                 ( int )
```

 The backlog argument defines the maximum length to which the queue of pending
 connections for sockfd may grow.

## accept()

Parametreleri:

```yaml
 1 : Socket file descriptor  ( int )
 2 : Socket address          ( *sockaddr )
 3 : Socket length           ( *socklen_t )
```

## memset()

Parametreleri:

```yaml
 1 : dest : Destination         ( *char )
 2 : c    : Character to fill   ( char  )
 3 : n    : Size                ( int   )
```

İstenilen bir karakteri (unsigned char), dest parametresindeki bellek bölgesinin ilk n parametre değeri kadar byte'ına kopyalar.

## recv()

Parametreleri:

```yaml
 1 : Socket file descriptor  ( int )
 2 : Buffer                  ( *void )
 3 : Buffer length           ( size_t )
 4 : Flags                   ( int )
```

## send()

Parametreleri:

```yaml
 1 : Socket file descriptor ( int )
 2 : Buffer                 ( *void )
 3 : Buffer length          ( size_t )
 4 : Flags                  ( int )
```

## sendto()

Parametreleri:

```yaml
 1 : Socket file descriptor ( int )
 2 : Buffer                 ( *void )
 3 : Buffer length          ( size_t )
 4 : Flags                  ( int )
 5 : Socket address         ( *sockaddr )
 6 : Socket length          ( socklen_t )
```

## recvfrom()

Parametreleri:

```yaml
 1 : Socket file descriptor ( int )
 2 : Buffer                 ( *void )
 3 : Buffer length          ( size_t )
 4 : Flags                  ( int )
 5 : Socket address         ( *sockaddr )
 6 : Socket length          ( *socklen_t )
```
