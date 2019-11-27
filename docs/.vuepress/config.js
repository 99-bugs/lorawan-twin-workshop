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
        // path: '/lorawan/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
        sidebarDepth: 0,    // optional, defaults to 1
        children: [
          '/sodaq-explorer/',
          '/sensors/'
        ]
      },
      {
        title: 'Het internet',   // required
        // path: '/lorawan/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
        sidebarDepth: 0,    // optional, defaults to 1
        children: [
          '/lorawan/'
        ]
      },
      {
        title: 'De server',   // required
        // path: '/lorawan/',      // optional, which should be a absolute path.
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
        // path: '/lorawan/',      // optional, which should be a absolute path.
        collapsable: true, // optional, defaults to true
        sidebarDepth: 1,    // optional, defaults to 1
        children: [
          '/iot-dashboard/'
        ]
      },

    ],
  },
  markdown: {
    lineNumbers: true,

  },
  serviceWorker: true,
}