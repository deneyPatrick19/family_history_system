<template>
  <div id="background">
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
          <el-button type="primary" v-on:click="signup">登录</el-button>
        </div>
      </el-card>
    </div>
  </div>
</template>

<style scoped>
.el-avatar{
  position:absolute;
  right: 5%;
  top:5%
}
#background{
  position:fixed;
  height: 100%;
  width:100%;
  top:0;
  left:0;
  color:rgb(77, 209, 213);
  background-image: linear-gradient(
    90deg,
    cyan,
    gray
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
  left:40%;
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
  left:35%;
  top:30%;
}

</style>

<script>
import axios from 'axios'
export default{
  data(){
    return {
      "username":"",
      "password":"",
    }
  },

  methods:{
  signup:function(e){
    axios.post("http://localhost:8080/user", {    
        id : 45,
        username: this.username,
        password: this.password,
    }).then((res) => {
      console.log(res.data);
      if (res.data){
        this.$router.push("/welcome")
      }else{
        alert("登录失败！")
      }
    }).catch((error) => {
      console.log(error);
    })
  }
  }
}
</script>
