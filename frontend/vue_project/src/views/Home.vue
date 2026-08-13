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
        { id: "个人信息", path: "/personal-history" },
        { id: "家谱表管理", path: "/family-table-manager" },
        { id: "成员列表", path: "/member-list" }
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
/* 顶层容器：占满视口 */
.home {
  width: 100%;
  height: 100vh;
  overflow: hidden;             /* home 自身不滚动，由内部 main 区域滚动 */
  display: flex;
  flex-direction: column;
}

.el-container {
  height: 100%;
}

/* 横向布局：sidebar + main */
.el-container > .el-container {
  flex: 1;
  min-height: 0;                /* 关键：允许 flex 子项收缩，让内部 overflow 生效 */
}

#header {
  background-color: #42ade7;
  height: 60px !important;       /* 覆盖 element-plus 默认 60px */
  padding: 0;
  margin: 0;
  flex-shrink: 0;                /* 顶栏高度固定不被压缩 */
}

#sidebar {
  width: 160px;
  background-color: #fff;
  text-align: left;
  overflow-y: auto;              /* 菜单过长时只在 sidebar 内滚动 */
  flex-shrink: 0;
}

/* 主内容区：唯一纵向滚动容器 */
#main_content {
  background-color: rgb(242, 239, 239);
  padding: 0;
  overflow: hidden;             /* 滚动交由 .main-bg 负责 */
}

/* 内容卡片：内部填充 + 单一滚动轴 */
.main-bg {
  height: 100%;
  background: #fff;
  border-radius: 4px;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.08);
  padding: 16px 24px;
  margin: 12px;
  box-sizing: border-box;
  overflow-y: auto;             /* 仅纵向滚动 */
  overflow-x: hidden;           /* 禁用横向滚动 */
  scrollbar-width: none;        /* Firefox 隐藏滚动条 */
  -ms-overflow-style: none;     /* IE/Edge 隐藏滚动条 */
}

/* WebKit (Chrome/Safari/Edge) 隐藏滚动条 */
.main-bg::-webkit-scrollbar {
  display: none;
}

/* 菜单样式 */
.el-menu-item {
  font-size: 15px;
}

.router-link-active {
  text-decoration: none;
}

.active {
  background-color: #3498db;
  color: white;
}

/* 顶栏内部布局 */
.header-content {
  position: relative;
  display: flex;
  justify-content: space-between;
  align-items: center;
  height: 100%;
  width: 100%;
  box-sizing: border-box;
  padding: 0 24px;
}

.header-title {
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
  font-size: 22px;
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

/* 响应式：窄屏收起侧边栏宽度 */
@media (max-width: 768px) {
  #sidebar {
    width: 120px;
  }
  .header-title {
    font-size: 18px;
  }
}
</style>
