import asyncio
import websockets

async def hello():
    async with websockets.connect(
            'ws://localhost:8765') as websocket:
        name = input("What's your name? ")

        await websocket.send(name)
        print(f"> {name}")

        greeting = await websocket.recv()
        print(f"< {greeting}")


async def myClient():
    async with websockets.connect(
            'ws://localhost:8765')as websocket:
        
        while(1):    
            msg = input("C:")
            await websocket.send(msg)
    
            msg = await websocket.recv()
            print("S:",msg)
            if(msg == "end"):
                break
        

        
#asyncio.get_event_loop().run_until_complete(hello())
asyncio.get_event_loop().run_until_complete(myClient())
