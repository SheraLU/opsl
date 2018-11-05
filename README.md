# 配置

项目属性（保留原有!!不要删除<不同选项>）
--------
> C/C++
>> 附加包含目录
>
> 链接器
>> 常规--附加库目录
>
>> 输入--附加依赖项

本地设置
--------
>新建code文件夹
>
>AListener.cpp中
>```c++
>/*设置本地路径*/
>void Alistener::on_data_available(DDS::DataReader_ptr reader){
>...
>getAllFiles("code文件夹位置", fs);
>...
>}
>```
>
>codehistory.cpp中
>```c++
>/*设置本地路径*/
>void CodeHistory::getfiles(QString ip){
>...
>getAllFiles("code文件夹位置", fs);
>...
>}
>```
