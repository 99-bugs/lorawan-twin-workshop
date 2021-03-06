module.exports = {
  title: 'LoRaWAN Workshop',
  description: 'Introductie tot LoRaWAN aan de hand van een STEM workshop',
  themeConfig: {
    nav: [
      {text: 'VIVES', link: 'https://www.vives.be'}
    ],
    displayAllHeaders: false,
    sidebar: 'auto',
    repo: '99-bugs/lorawan-twin-workshop',
    sidebar: [
      {
        title: 'De things',   // required
        collapsable: true, // optional, defaults to true
        sidebarDepth: 0,    // optional, defaults to 1
        children: [
          '/sodaq-explorer/',
          {
            title: 'Grove sensoren',   // required
            path: '/sensors/',      // optional, which should be a absolute path.
            collapsable: true, // optional, defaults to true
            sidebarDepth: 0,    // optional, defaults to 1
            children: [
              '/sensors/push_button/',
              '/sensors/switch/',
              '/sensors/q_touch/',
              '/sensors/rfid/',
              '/sensors/motion-sensor/',
              '/sensors/rotary-sensor/',
              '/sensors/tph-sensor/',
            ]
          },
        ]
      },
      {
        title: 'Het internet',   // required
        path: '/lorawan/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
      },
      {
        title: 'De server',   // required
        collapsable: true, // optional, defaults to true
        sidebarDepth: 0,    // optional, defaults to 1
        children: [
          '/lamp/',
          '/mosquitto/',
          '/node-red/'
        ]
      },
      {
        title: 'Het dashboard',   // required
        path: '/iot-dashboard/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
      },
    ],
  },
  markdown: {
    lineNumbers: true,

  },
  serviceWorker: true,
  plugins: [
    ['vuepress-plugin-zooming', {
      // selector for images that you want to be zoomable
      // default: '.content img'
      selector: 'img',

      // make images zoomable with delay after entering a page
      // default: 500
      // delay: 1000,

      // options of zooming
      // default: {}
      options: {
        bgColor: 'black',
        zIndex: 10000,
      },
    }],
    ['@dovyp/vuepress-plugin-clipboard-copy', true]
  ],
}