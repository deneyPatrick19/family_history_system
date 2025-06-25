<template>
  <div class="home">
    <el-container style="width: 100%;">
      <el-header id="header">
        <div class="header-content">
          <h1 class="header-title">家庭族谱管理系统</h1>
          <div class="header-user">
            <span class="username">{{ username }}</span>
            <el-button type="text" @click="logout" style="color: #000;">退出登录</el-button>
          </div>
        </div>
      </el-header>
      <el-container style="width: 100%;">
        <el-aside id="sidebar">
          <el-menu :router="true" :default-active="$route.path">
            <el-menu-item v-for="(item, index) in menuItems" :key="index" :index="item.path">
              {{ item.id }}
            </el-menu-item>
          </el-menu>
        </el-aside>
        <el-main id="main_content">
          <div class="main-bg">
            <router-view></router-view>
          </div>
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>

<script>
export default {
  name: "Home",
  data() {
    return {
      menuItems: [
        { id: "首页", path: "/home" },
        { id: "个人信息", path: "/member-history" },
        { id: "添加家族关系", path: "/add-member" },
        { id: "家族树管理", path: "/family-tree" }
      ]
    }
  },
  computed: {
    username() {
      return this.$store.getters.user.username
    }
  },
  methods: {
    logout() {
      // 使用 store 退出登录
      this.$store.dispatch('logout');
      this.$router.push('/login');
    }
  },
  mounted() {
    // 页面加载时初始化用户信息
    this.$store.dispatch('initUser');
  }
}
</script>


<style scoped>
.el-container{
  height: 100%;
}
.main-bg {
  height: 98%;
  background: #fff;
  border-radius: 5px;
  box-shadow: 0 2px 12px rgba(0,0,0,0.08);
  padding: 4px 24px;
  margin: 2px;
  width: 100vw;
  height: 100vh;
  overflow-x: auto;
  overflow-y: auto;
}
.home {
  display: flex;
  flex-direction: column;
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
.header-content {
  position: relative;
  display: flex;
  justify-content: space-between;
  align-items: center;
  height: 100%;
  width: 100%;
  box-sizing: border-box;
  padding: 0 24px; /* 可选：让内容不贴边 */
}
.header-title {
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
  font-size: 24px;
  margin: 0;
  color: #fff;
  white-space: nowrap;
}
.header-user {
  display: flex;
  align-items: center;
  gap: 12px;
  z-index: 1;
}
.username {
  font-weight: bold;
  color: #fff;
}
</style>
