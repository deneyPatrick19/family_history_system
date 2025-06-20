<template>
  <div>
    <div style="font-size: 20px; color: green; font-style: italic ;" >
        HelloWorld!欢迎来到vue的世界!今天的调试完成了
    </div>
    <div>
      {{ a }}
    </div>
  </div>
</template>

<script setup>
import { ref } from "vue";


const a = ref("14")
</script>

