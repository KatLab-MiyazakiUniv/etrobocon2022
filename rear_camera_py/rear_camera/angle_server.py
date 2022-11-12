"""TCPサーバを起動し、リクエストに応じて登録されたコールバック関数を実行するモジュール."""

import socket
from typing import Callable


class AngleServer:
    """TCPサーバを起動し、リクエストに応じて登録されたコールバック関数を実行するクラス.

    Attributes:
        ENCODING (str): encodeやdecodeをする際に指定する文字コード.
    """

    ENCODING = "utf-8"

    def __init__(
        self,
        server_ip: str = "127.0.0.1",
        server_port: int = 10338,
        listen_num: int = 127,
        buf_size: int = 1024,
        debug: bool = False
    ) -> None:
        """コンストラクタ.

        Args:
            server_ip (str, optional): サーバのアドレス. Defaults to "127.0.0.1".
            server_port (int, optional): サーバのListenポート. Defaults to 10338.
            listen_num (int, optional): 最大同時接続数?. Defaults to 127.
            buf_size (int, optional): 受信データの最大サイズ?. Defaults to 1024.
            debug (bool, optional): デバッグモードを有効化する場合True. Defaults to False.
        """
        self.__server_ip = server_ip
        self.__server_port = server_port
        self.__listen_num = listen_num
        self.__buf_size = buf_size
        self.__debug = debug

        self.__command_dict = {}
        self.__tcp_server = None

    def __del__(self) -> None:
        """デストラクタ."""
        if self.__tcp_server is not None:
            # サーバを閉じる
            self.__tcp_server.close()

    def add_command(self, command: str, func: Callable[[str], str]) -> None:
        """コマンドとそれに対応するコールバック関数を設定する.

        Args:
            command (str): コマンド
            func (Callable[[str], str]): コールバック関数.
                                         引数はクライアントから送られてくるコマンドを含めた文字列1つのみ.
                                         戻り値は、文字列型1つのみ.
        """
        self.__command_dict[command] = func

    def run(self) -> None:
        """サーバを起動する."""
        # サーバの初期化
        self.__tcp_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__tcp_server.bind((self.__server_ip, self.__server_port))
        self.__tcp_server.listen(self.__listen_num)

        try:
            while True:
                # 新たなクライアントの接続を待つ
                client, address = self.__tcp_server.accept()
                if self.__debug:
                    print("[*] Connected!! [ Source: %s]" % str(address))

                # クライアントからデータを受け取る
                data = client.recv(self.__buf_size).decode(AngleServer.ENCODING)
                if self.__debug:
                    print("[*] Received Data: '%s'" % data)

                # リクエストの解析(カンマで区切った際、先頭の文字列がコマンド)
                command = data.split(",")[0].replace('\n', '')

                if command == 'quit':
                    client.send('OK'.encode(AngleServer.ENCODING))
                    client.close()
                    break

                # コマンドが見つからない場合
                if command not in self.__command_dict:
                    client.send("None".encode(AngleServer.ENCODING))
                    client.close()
                    if self.__debug:
                        print("[ERROR] Unknown command(%s)" % command)
                    continue

                # コマンドを実行する
                result = str(self.__command_dict[command](data))
                if self.__debug:
                    print("[INFO] command: %s, result: %s" % (command, result))
                client.send(result.encode(AngleServer.ENCODING))
                client.close()
        except:  # noqa
            pass  # エラーを握りつぶす代わりに、確実にCloseを行う
        if self.__debug:
            print("[INFO] Closing server...")
        self.__tcp_server.close()
        self.__tcp_server = None
