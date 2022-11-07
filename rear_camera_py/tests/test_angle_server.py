"""AngleServerクラスのテストコード."""

import unittest
import subprocess
import threading
import time


from rear_camera.angle_server import AngleServer


class TestCalibrator(unittest.TestCase):
    def test_server_command_only(self):
        server_ip = "127.0.0.1"
        # NOTE: また、サーバを終了しても使用していたポートはデフォルトで60秒間はTIME_WAIT状態になり、
        #       使用できない(Linuxの場合).
        #       そこで、70秒周期でポートを使いまわすようにしている.
        server_port = 11338 + (int(time.time()) % 70)
        listen_num = 127
        buf_size = 1024
        debug = False

        angle_server = AngleServer(
            server_ip=server_ip,
            server_port=server_port,
            listen_num=listen_num,
            buf_size=buf_size,
            debug=debug
        )

        # サーバへのハンドラの登録
        def echo_handler(arg: str) -> str:
            return arg.replace('\n', '')
        angle_server.add_command('echo', echo_handler)

        # サーバのスタート
        server_thread = threading.Thread(target=angle_server.run)
        server_thread.start()

        # サーバへコマンドを送る(実際のシェルスクリプトの代わり)
        command = 'echo'
        linux_command = ['bash', '-c', 'echo %s | nc %s %d' % (command, server_ip, server_port)]
        try:
            result = subprocess.check_output(linux_command)
        except Exception:
            pass  # エラーを握りつぶす
        expected = command

        # サーバへ終了コマンドを送信する
        command = 'quit'
        linux_command = ['bash', '-c', 'echo %s | nc %s %d' % (command, server_ip, server_port)]
        try:
            _ = subprocess.check_output(linux_command)
        except Exception:
            pass  # エラーを握りつぶす

        # サーバが終了するまで待つ
        server_thread.join()

        # 結果の確認
        self.assertEqual(expected, result.decode(AngleServer.ENCODING))

    def test_server_command_with_arguments(self):
        server_ip = "127.0.0.1"
        # NOTE: 上記のテストで使ったポートが解放されていない可能背があるため、
        #       同じポートは使いまわさない.
        #       また、サーバを終了しても使用していたポートはデフォルトで60秒間はTIME_WAIT状態になり、
        #       使用できない(Linuxの場合).
        #       そこで、70秒周期でポートを使いまわすようにしている.
        server_port = 11438 + (int(time.time()) % 70)
        listen_num = 127
        buf_size = 1024
        debug = False

        angle_server = AngleServer(
            server_ip=server_ip,
            server_port=server_port,
            listen_num=listen_num,
            buf_size=buf_size,
            debug=debug
        )

        # サーバへのハンドラの登録
        def echo_handler(arg: str) -> str:
            return arg.replace('\n', '')
        angle_server.add_command('tmp', echo_handler)

        # サーバのスタート
        server_thread = threading.Thread(target=angle_server.run)
        server_thread.start()

        # サーバへコマンドを送る(実際のシェルスクリプトの代わり)
        command = 'tmp,val0,val1,val2'
        linux_command = ['bash', '-c', 'echo %s | nc %s %d' % (command, server_ip, server_port)]
        try:
            result = subprocess.check_output(linux_command)
        except Exception:
            pass  # エラーを握りつぶす
        expected = command

        # サーバへ終了コマンドを送信する
        command = 'quit'
        linux_command = ['bash', '-c', 'echo %s | nc %s %d' % (command, server_ip, server_port)]
        try:
            _ = subprocess.check_output(linux_command)
        except Exception:
            pass  # エラーを握りつぶす

        # サーバが終了するまで待つ
        server_thread.join()

        # 結果の確認
        self.assertEqual(expected, result.decode(AngleServer.ENCODING))
