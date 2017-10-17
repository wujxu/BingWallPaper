# Ubuntu下简单的下载Bing每日一图作为壁纸的程序

使用方法：

1. 使用Qt编译生成`BingWallPaper`
2. 创建`~/Pictures/bing/`文件夹，把生成的`BingWallPaper`放入并执行一次
3. 设置壁纸为该目录下的`bing_today.jpg`
  
设置每日自动下载壁纸：
  * 在控制端中使用`crontab -e`命令打开自动作业文件，末尾添加`5 0 * * * /home/[username]/Pictures/bing/BingWallPaper`（每日00:05自动下载壁纸）
  * 打开`Startup Application`，添加`BingWallPaper`（开机自动下载壁纸）
