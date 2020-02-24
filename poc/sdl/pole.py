def FilledPolygon(*a):
    print(a)

length = 0.5
x_threshold = 2.4
x = (0, 10, 10, 100)

screen_width = 600
screen_height = 400

world_width = x_threshold*2
scale = screen_width/world_width
carty = 100
polewidth = 10.0
polelen = scale * (2 * length)
cartwidth = 50.0
cartheight = 30.0

if True:
    l,r,t,b = -cartwidth/2, cartwidth/2, cartheight/2, -cartheight/2
    axleoffset =cartheight/4.0
    FilledPolygon([(l,b), (l,t), (r,t), (r,b)])
    # carttrans = rendering.Transform()
    l,r,t,b = -polewidth/2,polewidth/2,polelen-polewidth/2,-polewidth/2
    pole = FilledPolygon([(l,b), (l,t), (r,t), (r,b)])
    # pole.set_color(.8,.6,.4)
    # poletrans = Transform(translation=(0, axleoffset))
    # axle = make_circle(polewidth/2)
    # axle.set_color(.5,.5,.8)
    # add_geom(axle)
    # track = Line((0,carty), (screen_width,carty))
    # track.set_color(0,0,0)

# Edit the pole polygon vertex
l,r,t,b = -polewidth/2,polewidth/2,polelen-polewidth/2,-polewidth/2
v = [(l,b), (l,t), (r,t), (r,b)]

cartx = x[0]*scale+screen_width/2.0 # MIDDLE OF CART
#carttrans.set_translation(cartx, carty)
#poletrans.set_rotation(-x[2])
