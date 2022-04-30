import websockets
import asyncio

async def hello(websocket,path):
    
    name = await websocket.recv()
    print(f"<{name}")

    greeting = f"Hello {name}!"
    await websocket.send(greeting)
    print(f"> {greeting}")

async def myServer(websocket,path):

    while(1):
        msg = await websocket.recv()
        if(msg == "end"):
            break
        print("C: ",msg)
        msg = input("S:")
        await websocket.send(msg)


#start_server = websockets.serve(hello,'localhost',8765)
start_server = websockets.serve(myServer,'localhost',8765)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
