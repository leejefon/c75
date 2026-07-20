/* My own cmd */

void other_cmd()
{
	  printf("\n");
	  printf("explorer   ----------	開啟檔案總管 (我的文件)\n");
	  printf("notepad    ----------	開啟記事本\n");
	  printf("calc       ----------	開啟計算機\n");
	  printf("write      ----------	開啟wordpad\n");
	  printf("mspaint    ----------	開啟小畫家\n");
	  printf("dvdplay    ----------	開啟DVD播放器 (Windows Media Player)\n");
	  printf("taskmgr    ----------	開啟工作管理員\n");
	  printf("magnify    ----------	開啟放大鏡\n");
	  printf("osk        ----------	開啟螢幕小鍵盤\n");
	  printf("charmap    ----------	啟動字元對應表\n");
	  printf("narrator   ----------	螢幕「講述人」\n");
	  printf("mstsc      ----------	遠端桌面連接\n");
	  printf("dxdiag     ----------	檢查DirectX資訊\n");
	  printf("winver     ----------	檢查Windows版本\n");
	  printf("mem.exe    ----------	檢查記憶體使用情況\n");
	  printf("Nslookup   ----------	IP位址偵測器\n");
	  printf("regedit.exe----------	註冊表\n");
}

int main()
{
	 char cmd[9999];
	 
	 do {

	 	 printf("\nJeff Lee's cmd.exe >> ");

		 gets(cmd);
	 
	 	 if (strcmp(cmd,"othercmd") == 0) other_cmd();
	 	 else system(cmd);

	 } while (strcmp(cmd,"exit"));

    return 0;
}
