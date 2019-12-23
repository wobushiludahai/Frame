'''
@Description: websockets server
@Author: landsea
@Date: 2019-12-23 19:16:34
@LastEditTime: 2019-12-23 19:26:45
@LastEditors: Please set LastEditors
'''
import asyncio
import websockets

@asyncio.coroutine
def echo(websockets, path):
    message = yield from websockets.recv()
    print('recv', message)
    server_data = "收到服务器端的数据"
    yield from websockets.send(server_data)

start_server = websockets.serve(echo, 'localhost', 8765)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
