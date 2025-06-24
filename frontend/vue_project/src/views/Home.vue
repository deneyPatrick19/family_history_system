<template>
  <div class="home">
    <el-container style= "width: 100%;">
      <el-header id="header">
        <h1 style="text-align: center; font-size: 24px;">家庭族谱管理系统</h1>
      </el-header>
      <el-container style="width: 100%;">
        <el-aside id="sidebar">
          <el-menu :router="true" >
            <el-menu-item v-for="(item, index) in menuItems" :key="index" 
            :class="{'active': activeItem === item}" @click="setActive(item)">
             <router-link :to="`${item.path}`" class="router-link-active"> {{ item.id }} </router-link> 
            </el-menu-item>
          </el-menu>
        </el-aside>
        <el-main id="main_content">
          <router-view></router-view>
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>

<script>
import router from '@/router';
export default{
  name:"Home",
  data(){
    return {
      menuItems: [
        {id:"首页", path: "/home"},
        {id:"个人信息", path: "/member-history"},
        {id:"添加家族关系", path: "/add-member"}],
      activeItem: null,
    }
  },
  methods:{
    home:function(){
      router.push("/home")
    },
    setActive(item) {
      this.activeItem = item;
    }
  },
}

</script>


<style scoped>
.el-container{
  height: 100%;
}
.home {
  display: flex;
  flex-direction: column;
  background-image: url("../assets/16pic_9345737_b.png");
  background-size: 100% 100%;
  background-attachment: fixed;
  width: 100%;
  height: 100%;
  justify-content: center;
  align-items: center;
}
.router-link-active {
  text-decoration: none;
}
#header{
  background-color: #42ade7;
  height: 66px;
  padding: 0px;
  margin: 0px;
}
#sidebar{
  width: 140px;
  background-color: rgb(255, 255, 255);
  text-align: left;
}
#main_content{
  background-color: rgb(242, 239, 239);
  /* border-radius: 8px; */
}
.active {
  background-color: #3498db;
  color: white;
}
.el-menu-item{
  font-size: 16px;
}
</style>
