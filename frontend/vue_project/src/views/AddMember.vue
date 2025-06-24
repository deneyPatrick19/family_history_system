<template>
  <div class="add-member">
    <h1>增加成员</h1>
    <form @submit.prevent="addMember">
      <label for="name">姓名:</label>
      <input type="text" id="name" v-model="newMember.name" required />
      
      <label for="dob">出生日期:</label>
      <input type="date" id="dob" v-model="newMember.dob" required />
      
      <label for="relationship">关系:</label>
      <select v-model="newMember.relationship">
        <option value="父辈">父辈</option>
        <option value="平辈">平辈</option>
        <option value="子辈">子辈</option>
      </select>
      
      <button type="submit">添加成员</button>
    </form>
  </div>
</template>

<script>
export default {
  data() {
    return {
      newMember: {
        name: '',
        dob: '',
        relationship: '子辈',
      }
    };
  },
  methods: {
    addMember() {
      // 在这里可以将新成员数据保存到数据库或者本地状态中
      alert('成员已添加');
    }
  }
};
</script>

<style scoped>
.add-member {
  max-width: 430px;
  margin: auto;
  text-align: left;
}
h1{
  position: absolute;
  left: 38%;
}
form{
  position: absolute;
  left: 38%;
  top: 20%;
}
label {
  display: block;
  margin-top: 10px;
}

input, select{
  width: 400px;
  padding: 8px;
  margin: 8px 0;
}
button {
  width: 60%;
  padding: 10px;
  background-color: #4CAF50;
  color: white;
  border: none;
  margin-top: 20px;
  cursor: pointer;
}
</style>
