<template>
  <div id="background">
    <h1>家庭族谱管理系统</h1>
    <div id="login">
      <el-card>
        <div class="card-header" style="font-size: 20px; font-weight: bold; text-align: center;">
          <span>注册</span>
        </div>
        <div id="form">
          <el-text style="color: black; padding-right: 15px; padding-left: 15px;">账号: </el-text>
          <el-input v-model="username" style="width: 210px" placeholder="请输入账号" />
          <el-text style="color: black; padding-right: 15px;padding-left: 15px;">密码: </el-text>
          <el-input v-model="password" style="width: 210px" placeholder="请输入密码" show-password/>
          <div>
            <el-button type="primary" v-on:click="signup">注册</el-button>
            <el-link type="primary" style="font-size: 12px;" href="http://localhost:5173/login">已有账号？点击登录</el-link>
          </div>
        </div>
      </el-card>
    </div>
  </div>
</template>

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
#logo{
  color:black;
  font-size:25px;
  top:15%;
  left:15%;
  font-weight: bold;
  font-style:italic;
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
.el-link{
  position: absolute;
  left: 60%;
}

</style>

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
    axios.post("http://localhost:8080/user/signup", {
        "username": this.username,
        "password": this.password,
    } 
    ).then(response => {
      console.log(response.data);
      if (response.data){
        alert("注册成功!");
        this.$router.push("/login")
      }else{
        alert("注册失败！您已拥有账户或该用户名被占用")
      }
    }).catch((error) => {
      console.log(error);
    })
  },
  }
}
</script>
