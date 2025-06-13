// const { SerialPort, ReadlineParser } = require('serialport')
const express = require('express');
const axios = require('axios');
const socketIo = require('socket.io');
const http = require('http');
const { dirname } = require('path');

//SERVIDOR
const app = express();
const server = http.createServer(app);

app.use(express.static('public')); //ADICIONA ARQUIVOS ESTÁTIVOS

app.get('/',(req,res,next) => {
    res.sendFile(__dirname + '/public/index.html');
})





const io = socketIo(server);

io.on('connection', (socket) => {
    // console.log('Um usuário conectado');
  
    // Simule a obtenção de dados da API (substitua pelo código da sua API real)
    setInterval(function () { 
    axios.get('http://192.168.1.7/')
      .then((response) => {
        const dadosDaApi = response.data;
        // Emita os dados para o cliente conectado

        socket.emit('dadosDaApi', dadosDaApi);

      })
      .catch((error) => {
        console.error('Erro ao buscar dados da API:', error);
      })
    },1000);
  
    socket.on('disconnect', () => {
      console.log('Usuário desconectado');
    });
  });

  server.listen(9999,()=>{
    console.log("Servidor rodando!");
})

//CONFIGURAÇÃO SERIAL DO ARDUINO

// const port = new SerialPort({ path: 'COM3', baudRate: 9600 })
// const parser = new ReadlineParser();
// port.pipe(parser)

// parser.on('data', (line)=>{
//     console.log('Arduino dice: ' + line)
//     io.emit('serial:data',{
//         Value:line
//     })
// })
