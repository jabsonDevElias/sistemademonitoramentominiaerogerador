# 🌬️ Painel de Monitoramento de Mini Aerogerador

Este projeto é um painel em tempo real para monitoramento de um **mini aerogerador**, desenvolvido com **Node.js**, **Express** e **WebSocket (Socket.io)**. Ele coleta dados como **voltagem**, **corrente**, e outras métricas enviadas por um microcontrolador **ESP-WROOM-32 (DOIT ESP32 DEVKIT V1)** e exibe em um painel web.

## ⚠️ Importante

> 🟡 **O servidor hospedado no ESP32 deve estar ligado e funcionando corretamente para que o painel receba os dados.**  
> 🔧 Você deve **copiar o IP exibido no monitor serial da IDE do Arduino** (como `192.168.1.x`) e **substituir no código Node.js**, na linha onde está a requisição `axios.get(...)`:

```js
axios.get('http://SEU-IP-AQUI/')
```

## 🚀 Tecnologias Utilizadas

- Node.js
- Express
- Socket.io
- ESP32 (ESP-WROOM-32)
- HTML, CSS, JavaScript

---

## 📡 Como Funciona

1. O ESP32 coleta dados do mini aerogerador (voltagem, corrente, etc.).
2. Os dados são enviados via HTTP para o servidor Node.js.
3. O servidor transmite os dados via WebSocket para o navegador.
4. O painel web atualiza em tempo real com os dados recebidos.

---

## 🧪 Instalação

1. Clone o repositório:
```bash
git clone https://github.com/jabsonDevElias/sistemademonitoramentominiaerogerador.git
cd sistemademonitoramentoniniaerogerador
```

2. Instale as dependências:

```bash 
npm install
````

3. Inicie o servidor:

```bash 
node server.js
````

4. Acesse o painel:

```bash 
http://localhost:9999
````
![Você deve conseguir vê isso](galeria/01.png)


