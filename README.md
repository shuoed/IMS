# IMS
信息管理系统<br />
C语言；CS架构；<br />
2018.08.11 实现在本地端 信息的增删改查。<br />
目前有两个功能：<br />
&nbsp;&nbsp;&nbsp;&nbsp;1. 网址信息存储：网站名称+网址<br />
&nbsp;&nbsp;&nbsp;&nbsp;2. 通讯录：姓名+手机号<br />
实体表：<br />
&nbsp;&nbsp;&nbsp;&nbsp;用户表：ID+昵称+密码+邮箱<br />
&nbsp;&nbsp;&nbsp;&nbsp;网站表：自增ID+网站名称+网址+备注<br />
&nbsp;&nbsp;&nbsp;&nbsp;通讯录表：自增ID+姓名+手机号+邮箱+备注<br />
关系表：<br />
&nbsp;&nbsp;&nbsp;&nbsp;用户网站关系表：用户ID+（网站表）自增ID<br />
&nbsp;&nbsp;&nbsp;&nbsp;用户通讯录关系表：用户ID+（通讯录表）自增ID<br />
    <br />
下一步计划：<br />
&nbsp;&nbsp;&nbsp;&nbsp;分为客户端和服务器端。利用socket编程实现用户的登录注册等功能。<br />
