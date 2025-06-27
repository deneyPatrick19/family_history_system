<template>
  <div id="background">
    <h1>家庭族谱管理系统</h1>
    <div id="login">
      <el-card>
        <div class="card-header" style="font-size: 20px; font-weight: bold; text-align: center;">
          <span>登录</span>
        </div>
        <div id="form">
          <el-text style="color: black; padding-right: 15px; padding-left: 15px;">账号: </el-text> 
          <el-input v-model="username" style="width: 210px" placeholder="请输入账号" />
          <el-text style="color: black; padding-right: 15px;padding-left: 15px;">密码: </el-text>
          <el-input v-model="password" style="width: 210px" placeholder="请输入密码" show-password/>
          <div>
            <el-button type="primary" @click="signup">登录</el-button>
            <a type="primary" style="font-size: 12px;" href="http://localhost:5173/signup">没有账号？点击注册</a>
          </div>
        </div>
      </el-card>
    </div>
  </div>
</template>

<script>
import axios from 'axios';
export default{
  data(){
    return {
      "username":"",
      "password":"",
    }
  },
  
  methods:{
  signup:function(e){
    var param = new URLSearchParams();
    param.append("username", this.username)
    param.append("password", this.password)
    axios.post("http://localhost:8080/user/login", param , {headers:{
      'Content-Type': 'application/x-www-form-urlencoded'
      }
    }
    ).then(response => {
      if (response.data.data && response.data.data.token != null) {
        // 使用 store 存储用户信息
        this.$store.dispatch('login', {
          username: response.data.data.username || this.username,
          token: response.data.data.token,
          id: response.data.data.id
        });
        this.$router.push("/home");
      } else {
        this.$message.error("登录失败！您的账号或密码不正确，若没有账号请先注册");
      }
    }).catch(() => {
      this.$message.error("登录失败！请检查网络连接");
    })
  },
  }
}
</script>


<style scoped>
h1{
  font-size: 50px;
  text-align: center;
}
#background{
  position:fixed;
  height: 100%;
  width:100%;
  top:0;
  left:0;
  background-image: linear-gradient(
    90deg,
    cyan,
    gray
    /* rgb(247, 246, 246) */
  );
}
#login{
  position:absolute;
  top:35%;
  left:38%;
}
.el-card{
  background-color:rgba(255, 2555, 255, 0.4);
  width: 369px;
  height: 200px;
}
#form{
  line-height: 45px;
  padding-left: 15px;
  padding-right: 15px;
}
.el-button{
  position:relative;
  left:25%;
}
a{
  position: absolute;
  left: 60%;
}

</style>
