# Мессенджер на Boost.Asio
Осваиваю Boost.Asio, для этого пишу этот мессенджер. Кратко о том, что планируется сделать:
* Свой протокол прикладного уровня
* Асинхронный сервер (+ базы данных, полный фарш)
* Асинхронный клиент
* Логгирование для сервера и клиента
* Возможно интерфейс на Qt5 для клиента
* Возможно прикручу ко всему этому TLS/SSL
* Возможно поверх прикручу EE2E

Что уже сделано:
* Заготовка ассинхронного сервера, обрабатывающего соединения (100% будет доработан) 
* Заготовка протокола (100% будет если не полностью, то основательно переделан)